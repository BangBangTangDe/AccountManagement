#define _CRT_SECURE_NO_WARNINGS//����scanf����
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
#include"card_service.h"
#include "model.h"
#include"global.h"
#include"tool.h"
#include"menu.h"   
#include"billing_service.h"
#include"money_file.h"
#include"card_file.h"
lpCardNode cardList = NULL;//����ָ��
int InitCardList() //��������
{
	lpCardNode h = NULL;//ͷָ��Ϊ��
	if (cardList == NULL) {
		h =(lpCardNode)malloc(sizeof(CardNode));//����ͷ�ڵ��ڴ�
		if (h != NULL)
		{
			h->next = NULL;  //ͷ�ڵ��
			cardList = h;  //ָ��ͷ�ڵ�
			return TRUE;
		}
	}
	return FALSE;
}
int checkCard(const char* pName, const char* pPwd, int * pInfo, Card **p)
{
	lpCardNode node = NULL;
	int nIndex = 0;
	Billing* pBilling = NULL;
	if (FALSE == getCard())
	{
		return NULL;
	}
	if (cardList != NULL)
		node = cardList;
	while (node != NULL)
	{
		if ((strcmp(node->data.Number, pName) == 0) && (strcmp(node->data.Password, pPwd) == 0))
		{
			*pInfo = nIndex;
			*p = &node->data;
			return 1;
		}
		node = node->next;
		nIndex++;
	}
	if (node == NULL)
		printf("�޸ÿ���Ϣ�����������룡\n");
	return NULL;
}
int Addcard(Card card)
{
	if (TRUE == saveCard_binary(&card, CARDPATHBINARY))
	{
		return TRUE;
	}
	return FALSE;

}
int queryCard(const char*pName,Card **pcard)
{
	//Card* pCard = NULL;
	//pCard = (Card *)malloc(sizeof(Card));
	lpCardNode p;//���ڱ������ҽ��
	if (FALSE==getCard()) {
		return NULL;
	}
	p = cardList;//ָ��ͷ���
	while(p!=NULL)
	{
		if (strcmp(p->data.Number, pName) == 0)
		{
			*pcard = &(p->data);
			/*pCard = &(p->data);
			return pCard; */ //���ҳɹ�
			return 1;
		}
		else {
			p = p->next;
		}
	}
	return 0;
}
int sub_exist(char a[],char b[])
{
	int alen = strlen(a);
	int blen = strlen(b);
	int i = 0, j = 0;
	while (i < alen)
	{
		while (a[i] == b[j] &&i<alen)
		{
			i++;
			j++;
		}
		if (j == blen)
		{
			return 1;
		}
		i = i - j + 1;
		j = 0;

	}
	return 0;
}
Card*  QueryCards(const char* pName,int* pIndex)
{
	lpCardNode q = NULL;  //���
	Card* pCard = NULL; //���濨��Ϣ
	if (FALSE == getCard())
	{
		return NULL;
	}

	pCard = (Card*)malloc(sizeof(Card)); //�����ڴ�
	if (pCard == NULL)
	{
		return NULL;
	}
	q = cardList->next;
	while (q != NULL) //δ��������β
	{
		if (sub_exist(q->data.Number, pName))  //����pname
		{
			pCard[*pIndex] = q->data;
			(*pIndex)++;
			pCard = (Card*)realloc(pCard, ((*pIndex) + 1) * sizeof(Card)); //���·����ڴ�
		}
		q = q->next; //ָ����һ��
	}
	return pCard;
}
Card* AllCards(int* length) //��ȡ���п���Ϣ��lengthΪ��ǰ�����
{
	lpCardNode q = NULL;  //���
	Card* pCard = NULL; //���濨��Ϣ
	int cnt = 0;
	if (FALSE == getCard())
	{
		return NULL;
	}

	pCard = (Card*)malloc(sizeof(Card)*(*length)); //�����ڴ�
	if (pCard == NULL)
	{
		return NULL;
	}
	q = cardList->next;
	while (q != NULL) //δ��������β
	{
		pCard[cnt] = q->data;
		cnt++;
		//pCard = (Card*)realloc(pCard, ((*length) + 1) * sizeof(Card)); //���·����ڴ�
		q = q->next; //ָ����һ��
	}
	return pCard;
}
int getCard() {
	int i = 0;
	Card* pCard = NULL;
	int nCount = 0;
	lpCardNode now = NULL; //��ǰβ���
	lpCardNode new = NULL; //��ӵ�
	if (cardList != NULL)
	{
		ReleaseCardList(); //���
	}
	InitCardList(); //�����б�
	nCount = getCardCount_binary(CARDPATHBINARY); //����
	if (nCount==0) {
		//printf("1");  
		return FALSE;
	}
	else if (nCount==-1) {
		printf("�ļ��޷��򿪣�\n");
		return FALSE;
	}

	pCard = (Card*)malloc(sizeof(Card) * nCount);  //���濨��Ϣ
	if (pCard!= NULL)
	{
		if (0 == readCard_binary(pCard, CARDPATHBINARY)) 
		{
			//printf("2");
			free(pCard);
			return FALSE;
		}
		for (i = 0, now = cardList; i< nCount; i++)
		{
			new = (lpCardNode)malloc(sizeof(CardNode));  //����洢�ռ�
			if (new == NULL)
			{
				free(pCard);
				return FALSE;
			}

		memset(new, 0, sizeof(CardNode)); //����ռ�
		new->data = pCard[i];   //����
		new->next = NULL;       
		now->next = new;           //���
		now = new;
	}  //forѭ��
	free(pCard);    //�ͷ�
	return TRUE;
}
return FALSE;
} //����
void ReleaseCardList()
{
	lpCardNode now = cardList; //��ǰ���
	lpCardNode then = NULL; //��һ�����
	while (now != NULL)
	{
		then = now->next;
		free(now); //�ͷŵ�ǰ
		now = then; //ת����һ��
	}
	cardList = NULL;

}
int AllMoney(Money *m)
{
	int pos = 0;
	FILE *fp = fopen(MONEYPATH,"rb+");
	if (!fp)
	{
		printf("�ļ���ʧ��\n");
		return 0;
	}
	while (!feof(fp))
	{
		if (fread(&m[pos], sizeof(Money), 1, fp) != NULL)
		{
			pos++;
		}
	}
	fclose(fp);
	return 1;
}