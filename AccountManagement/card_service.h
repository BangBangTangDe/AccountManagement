#ifndef CARD_SERVICE_H
#define CARD_SERVICE_H //����ͷ�ļ����ظ�����
#include"model.h"
int Addcard(Card card);
int getCard();
void ReleaseCardList();
int InitCardList();
int queryCard(const char* pName,Card **pcard);
Card *QueryCards(const char* pName, int* pIndex);
Card* AllCards(int* length);
int  checkCard(const char* pName, const char* pPwd,int  *pInfo,Card **p);


int AllMoney(Money *m);
#endif
