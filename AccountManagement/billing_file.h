#ifndef BILLING_FILE_H
#define BILLING_FILE_H //����ͷ�ļ����ظ�����
#include"model.h"

int saveBilling(const Billing* pBilling,const char *pPath);
int addBilling(const char *pName,Billing *pBilling);
int readBilling(BillingNode *pBilling,const char *pPath);
int getBillingCount(const char *pPath);
int updateBilling(const Billing* pBilling, const char* pPath, int nIndex);
#endif