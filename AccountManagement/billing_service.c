#include<stdlib.h>
#include<string.h>
#include <stdio.h>
#include"model.h"
#include"global.h"
#include"billing_file.h"


lpBillingNode billingList = NULL;

void initBillingList() {
	lpBillingNode head = NULL;
	if (billingList==NULL) {
		head = (lpBillingNode)malloc(sizeof(BillingNode));
		head->next = NULL;
		billingList = head;
	}
}
void releaseBillingList() {
	lpBillingNode cur = billingList;
	lpBillingNode next = NULL;
	while (cur!=NULL) {
		next = cur->next;
		free(cur);
		cur = next;
	}
	billingList = NULL;
}
int getBilling() {
	int nCount = 0;
	Billing* pBilling = NULL;
	lpBillingNode node = NULL;
	int i = 0;
	lpBillingNode cur = NULL;
	if (billingList != NULL) {

		releaseBillingList();
	}
	initBillingList();
	nCount = getBillingCount(BILLINGPATH);
	//printf("%d",nCount);
	pBilling = (Billing*)malloc(sizeof(Billing) * nCount);
	if (readBilling(billingList, BILLINGPATH))
	{
		return 1;
	}
	else
	{
		return 0;
	}
	/*if (pBilling != NULL) {
		if (FALSE == readBilling(pBilling, BILLINGPATH)) {
			free(pBilling);
			return FALSE;
		}
		for (i = 0, node = billingList; i < nCount; i++) {
			cur = (lpBillingNode)malloc(sizeof(BillingNode));
			if (cur == NULL) {
				free(pBilling);
				return FALSE;

			}
			memset(cur, 0, sizeof(BillingNode));
			cur->data = pBilling[i];
			cur->next = NULL;
			node->next = cur;
			node = cur;
		}
			free(pBilling);
			return TRUE;
		}
		return FALSE;*/
	
}
Billing* queryBilling(const char* pName, int* pIndex) {

	lpBillingNode node = NULL;
	int nIndex = 0;
	if (FALSE == getBilling()) {
		
		return NULL;
	}
	node = billingList;
	while (node != NULL) {
		if (strcmp(node->data.aCardName, pName) == 0 && node->data.nStatus == 0) {
			return &node->data;
		}
		node = node->next;
		nIndex++;
		*pIndex = nIndex;
	}
	return NULL;
}
