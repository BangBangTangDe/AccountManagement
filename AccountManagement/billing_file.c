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

	FILE* fp = NULL; // 文件结构体指针
	if ((fp = fopen(pPath, "rb+")) == NULL)
	{
		printf("文件无法正确打开!不能读取计费信息！\n");
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
	FILE* fp = NULL; // 文件结构体指针
	char aStart[20];
	char aEnd[20];
	if ((fp = fopen(pPath, "ab+")) == NULL)
	{
		printf("文件打开失败");
		return FALSE;
	}
	timeToString(pBilling->tStart, aStart);
	timeToString(pBilling->tEnd, aEnd);
	//fprintf(fp, "##%s##%s##%s##%f##%d##%d\n", pBilling->aCardName, aStart,aEnd,pBilling->fAmount,pBilling->nStatus,pBilling->nDel);
	//写入信息
	fwrite(pBilling, sizeof(Billing), 1, fp);
	fclose(fp);//关闭
	printf("**********计费信息成功存入文件***********\n");
	return TRUE;
}
int addBilling(const char *pName,Billing *pBilling) {
	strcpy(pBilling->aCardName,pName); //上机卡号
	pBilling->tStart = time(NULL);     //上机时间
	pBilling->tEnd = 0;   //下机时间
	pBilling->fAmount = 0;  //消费金额
	pBilling->nStatus = 0;   //消费状态
	pBilling->nDel = 0;//删除标识

	if (FALSE==saveBilling(pBilling,BILLINGPATH)) {

		return FALSE;
	}
	return TRUE;
}

int getBillingCount(const char *pPath) {
	FILE* fp = NULL; // 文件结构体指针
	int nCount = 0;
	char aBuf[100] = { 0 };
	//Billing* pBilling = (Billing*)malloc(sizeof(Billing));
	if ((fp = fopen(pPath, "r")) == NULL)
	{
		printf("文件无法正确打开!不能统计计费信息数量！\n");
		fclose(fp);
		return FALSE;
	}
	else {
		while (fgets(aBuf, sizeof(aBuf), fp) != NULL)
		{
			if (strlen(aBuf) != 0)
				nCount++;
			memset(aBuf, 0, 100);  //清空
			
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
	FILE* fp = NULL; // 文件结构体指针
// 追加模式打开文件
	timeToString(pBilling->tStart, aStart);
	timeToString(pBilling->tEnd, aEnd);

	if ((fp = fopen(pPath, "r+")) == NULL)
	{
		printf("文件无法打开，无法更新卡的信息\n");
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
