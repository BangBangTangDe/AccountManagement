#define _CRT_SECURE_NO_WARNINGS//消除scanf的unsafe报错
#include"stdio.h"
#include"stdlib.h"
#include"menu.h"   
#include< time.h>
#include "string.h"
#include"card_service.h"
#include"card_file.h"
#include"global.h"
#include"model.h"
#include"tool.h"
#include"service.h"
 //头文件引入
void mainMenu()
{
	printf("***********欢迎进入网吧管理系统************\n");
	printf("1.普通管理员界面\n");
	printf("2.超级管理员界面\n");
	printf("0.退出\n");
}
void manageMenu()
{
	printf("欢迎进入超级管理员界面\n");
	printf("1.删除卡用户\n");
	printf("2.修改计费信息\n");
	printf("0.退出\n");

}
void outputMenu()    //展示菜单
{
	printf("-----欢迎使用计费管理系统-----\n");
	printf("---菜单---\n");
	printf("1.添加卡\n");
	printf("2.查询卡\n");
	printf("3.上机\n");
	printf("4.下机\n");
	printf("5.充值\n");
	printf("6.退费\n");
	printf("7.查询统计\n");
	printf("8.注销卡\n");
	printf("9.返回\n");
	printf("0.退出系统\n");
	printf("请根据您所需的功能，输入0到8的数字选择对应功能:\n");

}
void addCard() //添加
{
	Card card; 
	Card *p=NULL;
	char number[30];    //用户名
	char password[20]; //密码
	char password2[20]; //确认密码
	struct tm* endTime; //截止时间
	struct tm* startTime; //开始时间
	int queren = 1;  //确认密码标志
	printf("请输入18位内的卡号：");
	scanf("%s", number);
	if (strlen(number) > 18 )//超过18位
	{
	printf("卡号仅允许1-18位，请重新操作！\n");
	return;
	}
	if (queryCardInfo(number,&p) != NULL)  //卡号重复
	{
		printf("该卡号已存在，请重新操作！\n");
		return;
	}
	 strcpy(card.Number, number); //卡号存入
		
			printf("请输入密码(长度为1-8位):\n");
			scanf("%s", password);
			if (strlen(password) > 8) {
				printf("密码超过8位，请重新输入密码(长度为1-8位):\n");
				scanf("%s", password);
			}
			printf("请确认密码(长度为1-8位):\n");
			
			while (queren) {
				scanf("%s", password2);
                if (strcmp(password, password2)) {
				printf("两次密码不一致，请重新确认密码(长度为1-8位):\n");
				
				}
				else {
					queren = 0;
				}
			}
	strcpy(card.Password, password); //密码存入
	printf("请输入卡内金额：");
		scanf("%f", & card.Balance);
		//卡初始化
		card.fTotalUse = card.Balance; //初始总金额
		card.Delete = 0;//未删除
		card.Status = 0;//初始状态为未上机
		card.UseCount = 0; //初始使用次数为0
		card.Start = card.End = card.LastTime = time(NULL); //从当前开始计算时间
		startTime = localtime( & card.Start);
		endTime = localtime(&card.End);   //时间转换
		endTime->tm_year = startTime->tm_year + 1;  //有效期为1年
		card.End = mktime(endTime);   //时间转换

		printf("----------------------------添加卡的信息----------------------------\n");
		printf("   此卡卡号     此卡密码    当前状态   开卡金额\n");

		printf("   %s          %s            %d      %f\n", card.Number, card.Password, card.Status, card.Balance);
		if (FALSE == addCardInfo(card))
			printf("-----抱歉，卡添加失败！-----\n");
	  else  printf("-----恭喜，卡添加成功！-----\n");
		/*后续操作菜单*/
		int t;
		printf("--------请选择您接下来的操作--------\n");
		printf("输入1：继续添加卡\n");
		printf("输入其他：回到主菜单\n");
		scanf("%d", &t);
		fflush(stdin);
		rewind(stdin); //清除缓存区
		switch (t) {
		case 1: //继续添加
		{
			addCard(); 
			break;
		}
		default:  //主菜单
		{
			break;
		}
		} //switch
} //函数
void query()  //查询卡信息
{
	char num[20]; //卡号
	Card* pCard = NULL;
	char aLastTime[20]; //时间
	int length = 0;  //要显示的个数
	int way = 0;  //查询方式
	int i,j; //循环
	int cardstore = getCardCount_binary(CARDPATHBINARY);//存储卡的数量
	printf("以下为可供选择的查询方式：\n");
	printf("1：  精确查询\n");
	printf("2：  模糊查询\n");
	printf("其他:展示所有用户信息\n");
	scanf("%d", &way);
	
	if (way == 1)  //精确查询
	{
		printf("请输入卡号(长度1-18):\n");
		scanf("%s", num);
		pCard = (Card *)malloc(sizeof(Card));

		queryCardInfo(num,&pCard);
		if (strcmp(pCard->Number,num)!=0)
		{
			printf("所查询的卡号不存在！\n");
		}
		else
		{
		
		printf("----------------------------以下为该卡信息----------------------------\n");
		printf("   此卡卡号    当前状态   当前余额         累计金额     使用次数       上次使用时间\n");
		char lasttime[20];
		timeToString(pCard->LastTime, lasttime);
        printf("   %s         %d       %f      %f         %d     %s\n", pCard->Number, pCard->Status, pCard->Balance, pCard->fTotalUse, pCard->UseCount,lasttime);
		}
	}
	else if (way == 2) //模糊查询
	{
		printf("请输入模糊查询的关键字(长度1-18):\n");
		scanf("%s", num);
		pCard=QueryCards(num, &length);
		if ((length)== 0)
		{
			printf("所查询的卡号不存在！\n");
		}
		else {
			printf("-----------------------以下为模糊查询到包含相关内容卡信息-----------------------\n");
			printf("   此卡卡号    当前状态   当前余额         累计金额     使用次数       上次使用时间\n");
			for (i = 0; i < length; i++)
			{
				timeToString(pCard[i].LastTime, aLastTime); //时间转换
				printf("   %s         %d       %f      %f         %d     %s\n", pCard[i].Number, pCard[i].Status, pCard[i].Balance, pCard[i].fTotalUse, pCard[i].UseCount, aLastTime);
			} //for
			free(pCard);
		} //else
	} //if
	else //展示所有信息
	{
		pCard = AllCards(&cardstore);
			printf("-----------------------以下为当前系统中所有卡的信息-----------------------\n");
			printf("   此卡卡号    当前状态   当前余额         累计金额     使用次数       上次使用时间\n");
			for (i = 0; i < cardstore; i++)
			{
				timeToString(pCard[i].LastTime, aLastTime);  //时间转换
				printf("   %s         %d       %f      %f         %d     %s\n", pCard[i].Number, pCard[i].Status, pCard[i].Balance, pCard[i].fTotalUse, pCard[i].UseCount, aLastTime);
			}
			free(pCard);
	}
	pCard = NULL;
	int t;
	/*后续操作菜单*/
	printf("--------请选择您接下来的操作--------\n");
	printf("输入1：继续查询卡信息\n");
	printf("输入其他：回到主菜单\n");
	scanf("%d", &t);
	fflush(stdin);
	rewind(stdin);
	switch (t) {
	case 1: //继续查询 
	{
		query(); 
		break;
	}
	default:  //主菜单
	{
		break;
	}
	} //switch
} //函数
void logon()
{
	char aName[30] = {0};
	char aPwd[20] = {0};
	Card* pCard = NULL;
	char aLastTime[30];
	LogonInfo* pInfo = NULL;
	int nResult = 0;
	printf("请输入上机的卡号：\n");
	scanf("%s",aName);
	if (strlen(aName) > 18)   //超过18位
	{
		printf("卡号仅允许1-18位，请重新操作！\n");
		return;
	}
	printf("请输入上机卡的密码：\n");
	scanf("%s", aPwd);
	pInfo = (LogonInfo*)malloc(sizeof(LogonInfo));
	nResult = doLogon(aName,aPwd,pInfo);
	switch (nResult) {
	case 0:
		printf("---------上机失败！---------\n");
		break;
	case 1:
		printf("--------上机的卡信息如下-----------\n");
		printf("   卡号       余额         上机时间     \n");
		timeToString(pInfo->tLogon,aLastTime);
		printf("    %s          %f           %s\n", pInfo->aCardName, pInfo->fBalance, aLastTime);
		printf("-------上机成功!---------\n");break;
	case 2:
		printf("----------该卡不能使用!-------\n");break;
	case 3:
		printf("----------余额不足!----------\n");break;
	}
	free(pInfo);
}
void ExitSystem()
{
	releaseList();
}
void settle() {

	char aName[18] = { 0 };
	char aPwd[8] = { 0 };
	int nResult = -1;
	SettleInfo* pInfo = NULL;
	char aStartTime[30] = { 0 };
	char aEndTime[30] = { 0 };
	pInfo = (SettleInfo*)malloc(sizeof(SettleInfo));
	printf("请输入下机卡号（长度1-18）");
	scanf("%s",aName);
	printf("请输入下机密码（长度1-8）");
	scanf("%s",aPwd);
	nResult = doSettle(aName,aPwd,pInfo);
	printf("\n");
	printf("--------------下机信息如下-----------\n");
	switch (nResult) {
	case 0:
	{
		printf("下机失败!\n");
		break;
	}
	case 1: {  
		printf("卡号            消费             余额              上机时间             下机时间\n");
		timeToString(pInfo->tStart,aStartTime);
		timeToString(pInfo->tEnd,aEndTime);
		printf("%s        %f         %f        %s         %s\n",pInfo->aCardName,pInfo->fAmount,pInfo->fBalance,aStartTime,aEndTime);
		printf("------------下机成功----------\n");
		break;
	}
	case 2: {
		printf("该卡未在使用\n");
		break;
	}
	case 3:{
		printf("卡余额不足\n");
		break;
	}
	default: {
		break;
	}
	}
	free(pInfo);
}
void addMoney()
{
	char aName[18] = { 0 };
	char aPwd[8] = { 0 };
	float fAmount = 0;
	MoneyInfo Minfo;
	int nResult = -1;

	printf("请输入充值卡号（长度1-18）");
	scanf("%s", aName);
	printf("请输入充值卡密码（长度1-8）");
	scanf("%s", aPwd);
	printf("请输入充值金额:");
	scanf("%f", &fAmount);
	strcpy(Minfo.cardname, aName);
	Minfo.fMoney = fAmount;
	nResult = doAddMoney(aName, aPwd, &Minfo);
	

	if (nResult == 1)
	{
		printf("\n");
		printf("--------------充值信息如下-----------\n");
		printf("卡号\t充值金额\t余额\n");
		printf("%s\t%f\t%f\t\n", Minfo.cardname, Minfo.fMoney, Minfo.fBalance);
	}
	else
	{
		printf("----------------充值失败----------------\n");
	}
}
void refundMoney()
{
	char aName[18] = { 0 };
	char aPwd[8] = { 0 };
	MoneyInfo Minfo;
	int nResult = -1;

	printf("请输入退费卡号（长度1-18）");
	scanf("%s", aName);
	printf("请输入退费卡密码（长度1-8）");
	scanf("%s", aPwd);
	strcpy(Minfo.cardname, aName);
	nResult = doRefoundMoney(aName, aPwd, &Minfo);
	switch (nResult)
	{
	case 0:
	{
		printf("********退费失败！***********\n");
		break;
	}
	case 1:
	{
		printf("\n");
		printf("--------------退费信息如下-----------\n");
		printf("卡号\t退费金额\t余额\n");
		printf("%s\t%f\t%f\t\n", Minfo.cardname, Minfo.fMoney, Minfo.fBalance);
		break;
	}
	case 2:
	{
		printf("**************此卡已经注销***************\n");
		break;
	}
	case 3:
	{
		printf("**************此卡余额不足***************\n");
		break;
	}
	default:
		break;
	}

	
}
void annul()
{
	Card p;
	printf("请输入退费卡号（长度1-18）");
	scanf("%s", p.Number);
	printf("请输入退费卡密码（长度1-8）");
	scanf("%s", p.Password);
	if (FALSE == annulCard(&p))
	{
		printf("注销失败!\n");
	}
	else
	{
		printf("**********注销信息如下************\n");
		printf("卡号\t退款金额\n");
		printf("%s\t%f", p.Number, p.Balance);
	}
}
void collectInfo()
{
	printf("***************查询统计*****************\n");
	printf("1.注销卡信息显示\n2.所有卡信息以及消费总额\n3.充值退费信息显示\n4.上下机信息显示\n0.退出\n");
	int ch=0;
	scanf("%d", &ch);
	switch (ch)
	{
	case 0:break;
	case 1: {
		annualCard();
		break;
		}
	case 2:
	{
		CardRecord();
		break;
	}
	case 3:
	{
		moneyRecord();
		break;
	}
	case 4:
	{
		billRecord();
		break;
	}
	default:
		break;
	}
}

//管理员功能
int delete_card()
{
	Card *pCard = NULL;
	int ncount = 0;
	char name[18];
	char aLastTime[20]; //时间
	int cardstore = getCardCount_binary(CARDPATHBINARY);//存储卡的数量
	pCard = AllCards(&cardstore);
	if (pCard == NULL)
	{
		printf("没有卡号！无法删除！");
		return 0;
	}
	printf("-----------------------以下为当前系统中所有卡的信息-----------------------\n");
	printf("   此卡卡号    当前状态   当前余额         累计金额     使用次数       上次使用时间\n");
	for (int i = 0; i < cardstore; i++)
	{
		timeToString(pCard[i].LastTime, aLastTime);  //时间转换
		printf("   %s         %d       %f      %f         %d     %s\n", pCard[i].Number, pCard[i].Status, pCard[i].Balance, pCard[i].fTotalUse, pCard[i].UseCount, aLastTime);
	}
	printf("输入删除卡号：");
	scanf("%s", name);
	for (ncount; ncount < cardstore; ncount++)
	{
		if (strcmp(pCard[ncount].Number, name) == 0)
		{
			break;
		}
	}
	if (pCard[ncount].Status == 1)
	{
		printf("此卡还没下机，删除失败！\n");
		return 0;
	}
	else if (ncount == cardstore)
	{
		printf("查找不到此卡！删除失败!\n");
		return 0 ;
	}
	else
	{
		if (ncount != cardstore - 1) {
			for (int i = ncount+1; i < cardstore; i++)
			{
				pCard[i-1] = pCard[i];
			}
		}
		FILE * fp = fopen(CARDPATHBINARY, "w");
		if (fp == NULL)
		{
			printf("文件打开失败!");
			return 0;
		}
		else
		{

			fwrite(pCard, sizeof(Card), cardstore - 1, fp);
			printf("删除成功!!!\n");
			fclose(fp);
			return 1;
		}
	}
}
void update_charge()
{
	int unit=0;
	float charge = 0;
	printf("输入计费单元：");
	scanf("%d", &unit);
	printf("输入计费单价：");
	scanf("%f", &charge);
	if (charge < 0 || unit < 0)
	{
		printf("输入不能小于0！");
		return;
	}
	else
	{
		FILE * fp = fopen(CHARGEPATH, "w+");
		fprintf(fp, "%d %f", unit, charge);
		printf("修改成功！");
		fclose(fp);
	}
}