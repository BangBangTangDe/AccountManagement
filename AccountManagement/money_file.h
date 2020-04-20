#ifndef MONEY_FILE_H
#define MONEY_FILE_H
#include"model.h"
int saveMoney(const Money *pmoney, const char * path);
int getMoneyCount_binary(const char* pPath);

#endif
