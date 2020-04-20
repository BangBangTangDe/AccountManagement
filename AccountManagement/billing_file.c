#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include"model.h"
#include"global.h"
#include"billing_file.h"
#include"tool.h"
int readBilling(BillingNode* pBilling, const char* pPath) {

	int nIndex = 0;
	BillingNode *p=NULL;
	BillingNode *q=NULL;
	Billing *one = NULL;
	p = pBilling;
	struct stat;

	FILE* fp = NULL; // �ļ��ṹ��ָ��
	if ((fp = fopen(pPath, "rb+")) == NULL)
	{
		printf("�ļ��޷���ȷ��!���ܶ�ȡ�Ʒ���Ϣ��\n");
		return FALSE;
	}
	else {
		while (!feof(fp)) {
			one = (Billing *)malloc(sizeof(Billing));
			fread(one,sizeof(Billing),1,fp);
			if (feof(fp))break;
			q = (struct BillingNode *)malloc(sizeof(struct BillingNode));
			q->data = *one;
			/*strcpy(q->data.aCardName, one[nIndex].ardName);
			q->data.fAmount = one[nIndex].fAmount;
			q->data.nDel = one[nIndex].nDel;
			q->data.nStatus = one[nIndex].nStatus;
			q->data.tEnd = one[nIndex].tEnd;
			q->data.tStart = one[nIndex].tStart;*/
			q->next = NULL;
			p->next = q;
			p = q;
			nIndex++;
		}
	}
	fclose(fp);
	return TRUE;
}
int saveBilling(const Billing*pBilling,const char *pPath) {
	FILE* fp = NULL; // �ļ��ṹ��ָ��
	char aStart[20];
	char aEnd[20];
	if ((fp = fopen(pPath, "ab+")) == NULL)
	{
		printf("�ļ���ʧ��");
		return FALSE;
	}
	timeToString(pBilling->tStart, aStart);
	timeToString(pBilling->tEnd, aEnd);
	//fprintf(fp, "##%s##%s##%s##%f##%d##%d\n", pBilling->aCardName, aStart,aEnd,pBilling->fAmount,pBilling->nStatus,pBilling->nDel);
	//д����Ϣ
	fwrite(pBilling, sizeof(Billing), 1, fp);
	fclose(fp);//�ر�
	printf("**********�Ʒ���Ϣ�ɹ������ļ�***********\n");
	return TRUE;
}
int addBilling(const char *pName,Billing *pBilling) {
	strcpy(pBilling->aCardName,pName); //�ϻ�����
	pBilling->tStart = time(NULL);     //�ϻ�ʱ��
	pBilling->tEnd = 0;   //�»�ʱ��
	pBilling->fAmount = 0;  //���ѽ��
	pBilling->nStatus = 0;   //����״̬
	pBilling->nDel = 0;//ɾ����ʶ

	if (FALSE==saveBilling(pBilling,BILLINGPATH)) {

		return FALSE;
	}
	return TRUE;
}

int getBillingCount(const char *pPath) {
	FILE* fp = NULL; // �ļ��ṹ��ָ��
	int nCount = 0;
	char aBuf[100] = { 0 };
	//Billing* pBilling = (Billing*)malloc(sizeof(Billing));
	if ((fp = fopen(pPath, "r")) == NULL)
	{
		printf("�ļ��޷���ȷ��!����ͳ�ƼƷ���Ϣ������\n");
		fclose(fp);
		return FALSE;
	}
	else {
		while (fgets(aBuf, sizeof(aBuf), fp) != NULL)
		{
			if (strlen(aBuf) != 0)
				nCount++;
			memset(aBuf, 0, 100);  //���
			
		}
		fclose(fp);
		//free(pBilling);
		return nCount;
	}

}
int updateBilling(const Billing* pBilling, const char* pPath, int nIndex) {
	int count=1;
	long lPosition = 0;
	Billing *pbBuf;
	char aStart[30];
	char aEnd[30];
	char aLast[30];
	FILE* fp = NULL; // �ļ��ṹ��ָ��
// ׷��ģʽ���ļ�
	timeToString(pBilling->tStart, aStart);
	timeToString(pBilling->tEnd, aEnd);

	if ((fp = fopen(pPath, "r+")) == NULL)
	{
		printf("�ļ��޷��򿪣��޷����¿�����Ϣ\n");
		return FALSE;

	}
	while (count < nIndex) {
		pbBuf = (Billing *)malloc(sizeof(Billing));
		fread(pbBuf, sizeof(Billing), 1, fp);
		lPosition = ftell(fp);
		count++;
		free(pbBuf);
	}

	fseek(fp, lPosition, 0);
	//fprintf(fp, "##%s##%s##%s##%f##%d##%d\n", pBilling->aCardName, aStart, aEnd, pBilling->fAmount, pBilling->nStatus, pBilling->nDel);
	fwrite(pBilling, sizeof(Billing), 1, fp);
	
	fclose(fp);
	return TRUE;
}
