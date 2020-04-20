#ifndef CARD_SERVICE_H
#define CARD_SERVICE_H //����ͷ�ļ����ظ�����
#include"model.h"
//�ı���д����
int saveCard(const Card* pCard, const char* pPath);
int readCard(Card* pCard, const char* pPath);
int updateCard(const Card* pCard, const char* pPath, int nIndex);
Card praseCard(char* pBuf);
int getCardCount(const char* pPath);
//�����ƶ�д����
int saveCard_binary(const Card* pCard, const char* pPath);
int readCard_binary(Card* pCard, const char* pPath);
int getCardCount_binary(const char* pPath);
int updateCard_binary(const Card* pCard, const char* pPath, int nIndex);
#endif