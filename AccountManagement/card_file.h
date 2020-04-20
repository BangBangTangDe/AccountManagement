#ifndef CARD_SERVICE_H
#define CARD_SERVICE_H //避免头文件被重复包含
#include"model.h"
//文本读写操作
int saveCard(const Card* pCard, const char* pPath);
int readCard(Card* pCard, const char* pPath);
int updateCard(const Card* pCard, const char* pPath, int nIndex);
Card praseCard(char* pBuf);
int getCardCount(const char* pPath);
//二进制读写操作
int saveCard_binary(const Card* pCard, const char* pPath);
int readCard_binary(Card* pCard, const char* pPath);
int getCardCount_binary(const char* pPath);
int updateCard_binary(const Card* pCard, const char* pPath, int nIndex);
#endif