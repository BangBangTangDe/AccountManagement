#define _CRT_SECURE_NO_WARNINGS//消除scanf警告
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
lpCardNode cardList = NULL;//链表指针
int InitCardList() //创建链表
{
	lpCardNode h = NULL;//头指针为空
	if (cardList == NULL) {
		h =(lpCardNode)malloc(sizeof(CardNode));//分配头节点内存
		if (h != NULL)
		{
			h->next = NULL;  //头节点空
			cardList = h;  //指向头节点
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
		printf("无该卡信息，请重新输入！\n");
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
	lpCardNode p;//用于遍历查找结点
	if (FALSE==getCard()) {
		return NULL;
	}
	p = cardList;//指向头结点
	while(p!=NULL)
	{
		if (strcmp(p->data.Number, pName) == 0)
		{
			*pcard = &(p->data);
			/*pCard = &(p->data);
			return pCard; */ //查找成功
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
		while (a[i] == b[i] &&i<alen)
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
	lpCardNode q = NULL;  //结点
	Card* pCard = NULL; //储存卡信息
	if (FALSE == getCard())
	{
		return NULL;
	}

	pCard = (Card*)malloc(sizeof(Card)); //分配内存
	if (pCard == NULL)
	{
		return NULL;
	}
	q = cardList->next;
	while (q != NULL) //未遍历到表尾
	{
		if (sub_exist(q->data.Number, pName))  //查找pname
		{
			pCard[*pIndex] = q->data;
			(*pIndex)++;
			pCard = (Card*)realloc(pCard, ((*pIndex) + 1) * sizeof(Card)); //重新分配内存
		}
		q = q->next; //指向下一个
	}
	return pCard;
}
Card* AllCards(int* length) //获取所有卡信息，length为当前链表表长
{
	lpCardNode q = NULL;  //结点
	Card* pCard = NULL; //储存卡信息
	int cnt = 0;
	if (FALSE == getCard())
	{
		return NULL;
	}

	pCard = (Card*)malloc(sizeof(Card)*(*length)); //分配内存
	if (pCard == NULL)
	{
		return NULL;
	}
	q = cardList->next;
	while (q != NULL) //未遍历到表尾
	{
		pCard[cnt] = q->data;
		cnt++;
		//pCard = (Card*)realloc(pCard, ((*length) + 1) * sizeof(Card)); //重新分配内存
		q = q->next; //指向下一个
	}
	return pCard;
}
int getCard() {
	int i = 0;
	Card* pCard = NULL;
	int nCount = 0;
	lpCardNode now = NULL; //当前尾结点
	lpCardNode new = NULL; //添加的
	if (cardList != NULL)
	{
		ReleaseCardList(); //清空
	}
	InitCardList(); //建立列表
	nCount = getCardCount_binary(CARDPATHBINARY); //数量
	if (nCount==0) {
		//printf("1");  
		return FALSE;
	}
	else if (nCount==-1) {
		printf("文件无法打开！\n");
		return FALSE;
	}

	pCard = (Card*)malloc(sizeof(Card) * nCount);  //保存卡信息
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
			new = (lpCardNode)malloc(sizeof(CardNode));  //分配存储空间
			if (new == NULL)
			{
				free(pCard);
				return FALSE;
			}

		memset(new, 0, sizeof(CardNode)); //分配空间
		new->data = pCard[i];   //数据
		new->next = NULL;       
		now->next = new;           //后继
		now = new;
	}  //for循环
	free(pCard);    //释放
	return TRUE;
}
return FALSE;
} //函数
void ReleaseCardList()
{
	lpCardNode now = cardList; //当前结点
	lpCardNode then = NULL; //下一个结点
	while (now != NULL)
	{
		then = now->next;
		free(now); //释放当前
		now = then; //转到下一个
	}
	cardList = NULL;

}
int AllMoney(Money *m)
{
	int pos = 0;
	FILE *fp = fopen(MONEYPATH,"rb+");
	if (!fp)
	{
		printf("文件打开失败\n");
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