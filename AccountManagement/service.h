#ifndef SERVICE_H
#define SERVICE_H
#include"model.h"
int doLogon(const char *pName,const char *pPwd,LogonInfo *pInfo);
int addCardInfo(Card card);
int queryCardInfo(const char *pName,Card **pcard);
void releaseList();
int doSettle(const char *pName,const char *pPwd,SettleInfo *pInfo);
int doAddMoney(const char *pName, const char *pPwd, MoneyInfo *moneyinfo);
int doRefoundMoney(const char *pName, const char *pPwd, MoneyInfo *moneyinfo);
double getAmount(time_t tStart);
int annulCard(Card *p);
int moneyRecord();
int CardRecord();
int billRecord();
#endif

