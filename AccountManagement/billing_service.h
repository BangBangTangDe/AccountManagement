#ifndef BILLING_SERVICE_H
#define BILLING_SERVICE_H
#include"model.h"
void initBillingList();
void releaseBillingList();
int getBilling();
BillingNode *GetBillList();
Billing* queryBilling(const char * pNmae,int* pIndex);
#endif
