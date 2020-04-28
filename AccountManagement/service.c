#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include"card_service.h"
#include"service.h"
#include"global.h"
#include "billing_file.h"
#include "card_file.h"
#include"model.h"
#include"billing_service.h"
#include"money_file.h"

int addCardInfo(Card card) {

	if (TRUE==saveCard_binary(&card,CARDPATHBINARY)) {
		return TRUE;

	}
	return FALSE;
}
int queryCardInfo(const char *pName,Card **pcard) {

	int flag=queryCard(pName,pcard);
	*pcard = *pcard;
	return flag;
}
int doLogon(const char* pName, const char* pPwd, LogonInfo* pInfo) {

	Card* pCard = NULL;
	pCard = (Card *)malloc(sizeof(Card));
	int nIndex = 0;
	Billing billing;
	checkCard(pName,pPwd,&nIndex,&pCard);

	if (pCard == NULL) {
		return FALSE;
	}
	if (pCard->Status!=0) {
		return UNUSE;
	}
	if (pCard->Balance<=0) {
		return ENOUGHMONEY;
	}

	pCard->Status = 1;
	pCard->UseCount++;
	pCard->LastTime = time(NULL);

	if (FALSE==updateCard_binary(pCard,CARDPATHBINARY,nIndex)) {

		return FALSE;
	}
	strcpy(billing.aCardName,pName);
	billing.tStart = time(NULL);
	billing.tEnd = 0;
	billing.nStatus = 0;
	billing.fAmount = 0;
	billing.nDel = 0;

	if (TRUE==saveBilling(&billing,BILLINGPATH)) {

		strcpy(pInfo->aCardName,pName);
		pInfo->fBalance = pCard->Balance;
		pInfo->tLogon = billing.tStart;
		return TRUE;
	}
	return FALSE;

}
int doSettle(const char* pName, const char* pPwd, SettleInfo* pInfo) {

	Card* pCard = NULL;
	Billing* pBilling = NULL;
	int nIndex = 0;
	int nPosition = 0;
	double dbAmount = 0.0;
	float fBalance = 0.0;
	pBilling = queryBilling(pName,&nPosition);
	if (!checkCard(pName, pPwd, &nIndex, &pCard))
	{
		printf("无该卡信息，请重新输入!\n");
		return FALSE;
	}

	if (pBilling==NULL) {
		//printf("无该卡信息，请重新输入!\n");
		return FALSE;
	}
	
	dbAmount = getAmount(pBilling->tStart);
	fBalance = pCard->Balance - (float)dbAmount;
	if (fBalance<0) {
		return ENOUGHMONEY;
	}
	pCard->Balance = fBalance;
	pCard->Status = 0;
	pCard->LastTime = time(NULL);
	if (FALSE==updateCard_binary(pCard,CARDPATHBINARY,nIndex)) {
		return FALSE;
	}
	
	pBilling->fAmount = (float)dbAmount;
	pBilling->nStatus = 1;
	pBilling->tEnd = time(NULL);
	
	
	if (FALSE == updateBilling(pBilling, BILLINGPATH, nPosition)) {
		return FALSE;
	}
	strcpy(pInfo->aCardName,pName);
	pInfo->fAmount = (float)dbAmount;
	pInfo->fBalance = fBalance;
	pInfo->tStart = pCard->LastTime;
	pInfo->tEnd = time(NULL);
	return TRUE;
}
double getAmount(time_t tStart) {


	int UNIT = 0;
	float CHARGE = 0;
	FILE *fp = fopen(CHARGEPATH, "rb+");
	if (fp == NULL)
	{
		printf("文件打开失败");
		return 0;
	}
	fscanf(fp,"%d%f", &UNIT, &CHARGE);

	double dbAmount = 0;
	int nCount = 0;
	int nSec = 0;
	int nMinutes = 0;
	time_t tEnd = time(NULL);

	nSec = (int)(tEnd - tStart);
	nMinutes = nSec / 60;
	if (nMinutes %UNIT==0) {
		nCount = nMinutes / UNIT;
	}
	else {
		nCount = nMinutes / UNIT + 1;
	}
	dbAmount = nCount * CHARGE;
	return dbAmount;
}
void releaseList() {
	ReleaseCardList();
	releaseBillingList();
}
int doAddMoney(const char *pName, const char *pPwd, MoneyInfo *moneyinfo)
{
	Card* pCard = NULL;
	Money m;
	pCard = (Card *)malloc(sizeof(Card));
	int nIndex = 0;
	checkCard(pName, pPwd, &nIndex, &pCard);

	if (strcmp(pCard->Number,pName)!=0) {
		printf("找不到该卡信息，充值失败!\n");
		return FALSE;
	}
	if (pCard->Status == UNUSE)
	{
		printf("卡已经不能使用,充值失败！\n");
		return FALSE;
	}
	pCard->Balance += moneyinfo->fMoney;
	pCard->fTotalUse += moneyinfo->fMoney;
	if (FALSE == updateCard_binary(pCard, CARDPATHBINARY, nIndex))
	{
		return FALSE;
	}
	strcpy(m.cardname, pCard->Number);
	m.tTime = time(NULL);
	m.nStatus = 0;
	m.nDel = 0;
	m.fMoney = moneyinfo->fMoney;
	if (TRUE == saveMoney(&m, MONEYPATH))
	{
		strcpy(moneyinfo->cardname, m.cardname);
		moneyinfo->fBalance = pCard->Balance;
		return TRUE;
	}
	return FALSE;
}
int doRefoundMoney(const char *pName, const char *pPwd, MoneyInfo *moneyinfo)
{
	Card* pCard = NULL;
	Money m;
	pCard = (Card *)malloc(sizeof(Card));
	int nIndex = 0;
	float fbalance = 0.0;
	checkCard(pName, pPwd, &nIndex, &pCard);

	if (strcmp(pCard->Number, pName) != 0) {
		printf("找不到该卡信息，退费失败!\n");
		return FALSE;
	}
	if (pCard->Status !=0)
	{
		return FALSE;
	}
	if (pCard->Status == UNUSE)
	{
		return UNUSE;
	}
	fbalance = pCard->Balance;
	if (fbalance <= 0)
	{
		return ENOUGHMONEY;
	}
	pCard->Balance = 0;
	pCard->fTotalUse -=fbalance;
	if (FALSE == updateCard_binary(pCard, CARDPATHBINARY, nIndex))
	{
		return FALSE;
	}
	strcpy(m.cardname, pCard->Number);
	m.tTime = time(NULL);
	m.nStatus = 1;
	m.nDel = 0;
	m.fMoney = fbalance;
	if (TRUE == saveMoney(&m, MONEYPATH))
	{
		strcpy(moneyinfo->cardname, m.cardname);
		moneyinfo->fBalance = pCard->Balance;
		moneyinfo->fMoney=fbalance;
		return TRUE;
	}
	return FALSE;
}
int annulCard(Card *p)
{
	Card *cur = NULL;
	Money m;
	int index = 0;
	if (p == NULL)
		return FALSE;
	checkCard(p->Number, p->Password, &index,&cur);
	if (cur == NULL ||cur->Status==UNUSE)
	{
		return FALSE;
	}
	p->Balance = cur->Balance;
	cur->Status = 2;
	cur->Delete = 1;
	cur->Balance = 0;
	cur->LastTime = time(NULL);
	if (updateCard_binary(cur, CARDPATHBINARY, index) == FALSE)
	{
		return FALSE;
	}
	strcpy(m.cardname, cur->Number);
	m.fMoney = p->Balance;
	m.nDel = 1;
	m.nStatus = 1;
	m.tTime = time(NULL);
	saveMoney(&m, MONEYPATH);
	return TRUE;
}
//查询统计函数
//注销卡信息展示
int annualCard()
{
	Card *pCard = NULL;
	char aLastTime[20]; //时间
	int cnt = 0;
	int num = getCardCount_binary(CARDPATHBINARY);//存储卡的数量
	//pCard = (Card *)malloc(sizeof(Card)*num);
	pCard = AllCards(&num);
	printf("**********注销卡信息****************\n");
	printf("	此卡卡号    当前状态   当前余额         累计金额     使用次数       上次使用时间\n");
	for (int i = 0; i < num; i++)
	{
		if (pCard[i].Status == UNUSE)
		{
			timeToString(pCard[i].LastTime, aLastTime);
			printf("	%s         %7d       %f      %f         %5d     %s\n", pCard[i].Number, pCard[i].Status, pCard[i].Balance, pCard[i].fTotalUse, pCard[i].UseCount, aLastTime);
			cnt++;
		}
	}
	printf("注销卡数量：%d\n", cnt);
}
//充值退费记录
int moneyRecord()
{
	char t[36] = { 0 };
	int rows = 0;
	int cnt = getMoneyCount_binary(MONEYPATH);
	Money *m = (Money *)malloc(sizeof(Money)*cnt);
	AllMoney(m);
	printf("**************充值退费记录***************\n");
	printf("卡号\t操作数额\t时间\t\t   说明\n");
	for (int i = 0; i < cnt; i++)
	{
		timeToString(m[i].tTime, t);
		printf("%s\t%f\t%s   ", m[i].cardname, m[i].fMoney, t);
		if (m[i].nStatus == 0)
			printf("充值\n");
		else
			printf("退费\n");
	}
	return TRUE;
}
//卡数量和总额
int CardRecord()
{
	Card *pCard = NULL;
	float money=0;
	float total = 0;
	char aLastTime[20]; //时间
	int cnt = 0;//注销卡
	int shangji=0;
	int xiaji=0;
	int num = getCardCount_binary(CARDPATHBINARY);//存储卡的数量
	pCard = AllCards(&num);
	for (int i = 0; i < num; i++)
	{
		if (pCard[i].Status == UNUSE)
		{
			cnt++;
		}
		else if (pCard[i].Status == 0)
		{
			xiaji++;
		}
		else if (pCard[i].Status == 1)
		{
			shangji++;
		}
		money += pCard[i].Balance;
		total += pCard[i].fTotalUse;
	}
	printf("************卡数量和金额****************\n");
	printf("****************卡数量:%d****************\n", num);
	printf("****************卡余额(总):%.2f****************\n", money);
	printf("****************消费总额:%.2f****************\n", total);
	printf("----------------------------------------------------\n");
	printf("注销卡数量：%d\n", cnt);
	printf("上机卡数量：%d\n", shangji);
	printf("正常卡数量：%d\n", xiaji);
}
//统计上下机消费记录
int billRecord() {
	
	lpBillingNode node = NULL;
	if (FALSE == getBilling()) {

		return NULL;
	}
	node = GetBillList()->next;
	char t[36] = { 0 };
	char e[36] = { 0 };
	printf("**************上下机记录***************\n");
	printf("卡号\t消费金额\t上机时间\t下机时间\t说明\n");
	for (node; node!=NULL; node=node->next)
	{
		timeToString(node->data.tStart, t);
		if(node->data.nStatus==0)
		printf("%s\t%f\t%s\t未下机\t未结算\n", node->data.aCardName, node->data.fAmount, t);
		else {
			timeToString(node->data.tEnd, e);
			printf("%s\t%f\t%s\t%s\t结算\n", node->data.aCardName, node->data.fAmount, t,e);
		}
	}
	return TRUE;
}
