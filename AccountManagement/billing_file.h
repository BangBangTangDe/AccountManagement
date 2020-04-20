#ifndef BILLING_FILE_H
#define BILLING_FILE_H //避免头文件被重复包含
#include"model.h"

int saveBilling(const Billing* pBilling,const char *pPath);
int addBilling(const char *pName,Billing *pBilling);
int readBilling(BillingNode *pBilling,const char *pPath);
int getBillingCount(const char *pPath);
int updateBilling(const Billing* pBilling, const char* pPath, int nIndex);
#endif