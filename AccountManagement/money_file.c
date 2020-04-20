#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include"model.h"
#include"global.h"
int saveMoney(const Money *pmoney, const char * path)
{
	FILE *fp = fopen(path, "rb+");
	if (!fp)
	{
		printf("文件访问失败\n");
		fclose(fp);
		return FALSE;
	}
	fseek(fp, 0, SEEK_END);
	fwrite((const char *)pmoney, sizeof(Money), 1, fp);
	printf("\n充值退费信息成功存入文件\n");
	fclose(fp);
	return TRUE;

}
int getMoneyCount_binary(const char* pPath) {
	int ncount = 0;
	Money p;
	FILE * fp = fopen(pPath, "rb+");
	if (!fp)
	{
		printf("文件打开失败");
		return FALSE;
	}
	else
	{
		while (!feof(fp))
		{
			if (fread((char*)(&p), sizeof(Money), 1, fp) != 0)
				ncount++;
		}
		fclose(fp);
		return ncount;
	}

}