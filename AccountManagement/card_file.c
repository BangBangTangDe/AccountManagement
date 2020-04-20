#define _CRT_SECURE_NO_WARNINGS//消除scanf警告
#define CARDCHARNUM 300
#include "card_file.h"
#include "stdio.h"
#include"model.h"
#include"global.h"
#include "time.h"
#include "string.h"
#include "tool.h"
#include"stdlib.h"
#include<stdlib.h>
//文本读写
int saveCard(const Card* pCard, const char* pPath)
{
	char aStart[30];
	char aEnd[30];
	char aLast[30];  //时间转换字符串

	timeToString(pCard->Start, aStart);
	timeToString(pCard->End, aEnd);
	timeToString(pCard->LastTime, aLast);

	FILE* fp = NULL; // 文件结构体指针
// 追加模式打开文件
	if ((fp = fopen(pPath, "rb+")) == NULL)
	{
		printf("文件打开失败");
		return FALSE;
	}
	fseek(fp, 0, SEEK_END);
	fprintf(fp, "##%s##%s##%d##%s##%s##%f##%s##%d##%f##%d\n", pCard->Number, pCard->Password, pCard->Status, aStart, aEnd, pCard->fTotalUse, aLast, pCard->UseCount, pCard->Balance, pCard->Delete);
	//写入信息

	fclose(fp);//关闭

	return TRUE;
}
int readCard(Card* pCard, const char* pPath) {

	int nIndex = 0;   //信息个数
	int i = 0;           //结构体数组技术计数
	char aBuf[CARDCHARNUM] = { 0 };  //读取的数据
	FILE* fptr;

	if ((fptr = fopen(pPath, "rb")) != NULL)   //只读
	{
		while (fgets(aBuf, sizeof(aBuf), fptr) != NULL)
		{

			if (strlen(aBuf)!= 0) {
				pCard[i] = praseCard(aBuf);  //分解信息存入结构体数组
			}
			i++;
			memset(aBuf, 0, CARDCHARNUM);
		}
	}
	else {
		printf("文件打开失败!无法读取卡信息!");
		fclose(fptr);
		return FALSE;
	}
	fclose(fptr);
	return TRUE;
}
Card praseCard(char* pBuf) {
	Card card;
	char flag[10][20];
	char* buf=(char *)malloc(sizeof(char)*256);
	char* str = (char *)malloc(sizeof(char) * 20);   //分解的字符串
	int index = 0; //下标
	strcpy(buf , pBuf);  //解析字符串
	while ((str = strtok(buf, "##")) != NULL) {
		strcpy(flag[index], str);
		buf = NULL;
		index++;
	}
	strcpy(card.Number, flag[0]);
	strcpy(card.Password, flag[1]);
	card.Status = atoi(flag[2]);
	card.Start = stringToTime(flag[3]);
	card.End = stringToTime(flag[4]);
	card.fTotalUse = atof(flag[5]);
	card.LastTime = stringToTime(flag[6]);
	card.UseCount = atoi(flag[7]);
	card.Balance = atof(flag[8]);
	card.Delete = atoi(flag[9]);
	//分解后依次保存到结构体数组中
	return card;
}
int getCardCount(const char* pPath) {
	int nIndex = 0;   //卡中信息个数
	char aBuf[CARDCHARNUM] = { 0 };   //读取的数据

	FILE* fptr;   //文件指针

	if ((fptr = fopen(pPath, "r")) != NULL)
	{

		while (fgets(aBuf, sizeof(aBuf), fptr) != NULL)
		{
			if (strlen(aBuf) != 0)
				nIndex++;
			memset(aBuf, 0, CARDCHARNUM);  //清空
		}
	}
	else {
		printf("文件打开失败!无法读取卡信息!");
		fclose(fptr);
		return -1;
	}
	fclose(fptr); //关闭
	return nIndex;

}
int updateCard(const Card* pCard, const char* pPath, int nIndex) {
	char aBuf[CARDCHARNUM] = { 0 };
	char aStart[30];
	char aEnd[30];
	char aLast[30];
	int nLine = 0;
	long lPosition = 0;

	timeToString(pCard->Start, aStart);
	timeToString(pCard->End, aEnd);
	timeToString(pCard->LastTime, aLast);

	FILE* fp = NULL; // 文件结构体指针
					 // 追加模式打开文件
	if ((fp = fopen(pPath, "rb+")) == NULL)
	{
		printf("文件无法打开，无法更新卡的信息\n");
		return FALSE;

	}
	while (nLine < nIndex && (!feof(fp))) {
		memset(aBuf, 0, CARDCHARNUM);
		fgets(aBuf, sizeof(aBuf), fp);
		lPosition = ftell(fp);
		nLine++;
	}
	fseek(fp, lPosition - strlen(aBuf), SEEK_SET);
	fprintf(fp, "##%s##%s##%d##%s##%s##%f##%s##%d##%f##%d", pCard->Number, pCard->Password, pCard->Status, aStart, aEnd, pCard->fTotalUse, aLast, pCard->UseCount, pCard->Balance, pCard->Delete);
	fclose(fp);
	return TRUE;
}
//二进制方式读写
int saveCard_binary(const Card* pCard, const char* pPath)
{
	FILE * fp = fopen(pPath, "rb+");
	if (!fp)
	{
		printf("文件打开失败！\n");
		return FALSE;
	}
	fseek(fp, 0, SEEK_END);
	fwrite((const char *)pCard, sizeof(Card),1,fp);
	printf("\n*****************卡信息已经存入文件***********\n");
	fclose(fp);
	return TRUE;
}
int readCard_binary(Card* pCard, const char* pPath)
{
	int index = 0;
	FILE * fp = fopen(pPath, "rb+");
	if (!fp)
	{
		printf("文件打开失败!\n");
		return FALSE;
	}
	else
	{
		while (!feof(fp))
		{
			if (fread((char*)(&pCard[index]),sizeof(Card),1,fp)!=0)
				index++;
		}
		fclose(fp);
		return TRUE;
	}
}
int getCardCount_binary(const char* pPath)
{
	int ncount = 0;
	Card p;
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
			if (fread((char*)(&p), sizeof(Card), 1, fp) != 0)
				ncount++;
		}
		fclose(fp);
		return ncount;
	}

}
int updateCard_binary(const Card* pCard, const char* pPath, int nIndex)
{
	int nLine = 1;
	long lPosition = 0;
	FILE* fp = NULL;
	Card *p = (Card *)malloc(sizeof(Card));
	if ((fp = fopen(pPath, "rb+")) == NULL)
	{
		printf("文件无法打开，无法更新卡的信息\n");
		return FALSE;

	}
	while (nLine < nIndex && (!feof(fp))) {;
		if(fread(p, sizeof(Card),1, fp)!=0)
			lPosition = ftell(fp);
		nLine++;
	}
	fseek(fp, lPosition, SEEK_SET);
	fwrite((const char*)pCard, sizeof(Card), 1, fp);
	printf("**************卡信息更新成功***************\n");
	fclose(fp);
	return TRUE;
}


