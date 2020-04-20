#ifndef MODEL_H
#define MODEL_H //避免头文件被重复包含

#include< time.h>
typedef struct Card
{
	char Number[18];  //账号
	char Password[8]; //密码
	int  Status;      //卡状态（0为未上机，1为正上机，2为卡已注销，3为卡已失效）
	time_t  Start;       //开卡时间
	time_t  End;         //卡的截止时间
	float   fTotalUse;     //累计金额
	time_t    LastTime;        //最后的时间
	int       UseCount;  //总计使用次数
	float     Balance;      //余额
	int       Delete;            //删除标识：0为未删除，1为已删除
}Card;
typedef struct CardNode
{
	Card data; //数据域
	struct CardNode* next;//指针域
}CardNode, * lpCardNode;
//消费信息结构体
typedef struct Billing {

	char aCardName[18];  //卡号
	time_t tStart;       //上机时间
	time_t tEnd;         //下机时间
	float fAmount;       //消费金额
	int nStatus;         //消费状态，0-未结算，1-已结算
	int nDel;            //删除标识，0-未删除，1-已删除
}Billing;
typedef struct LogonInfo {
	char aCardName[18];   //上机卡号
	time_t tLogon;        //上机时间
	float fBalance;       //上机时卡的余额；
}LogonInfo;
typedef struct BillingNode {
	Billing  data;
	struct BillingNode *next;
}BillingNode,*lpBillingNode;
typedef struct SettleInfo {
	char aCardName[18];
	time_t tStart;
	time_t tEnd;
	float fAmount;
	float fBalance;
}SettleInfo;
//充值退费结构体
typedef struct Money {
	char cardname[18];
	time_t tTime;
	int nStatus;//充值状态  0 充值  1退费
	float fMoney;
	int nDel;//删除标志  0未删除  1删除
}Money;
typedef struct MoneyInfo
{
	char cardname[18];
	float fMoney;
	float fBalance;
}MoneyInfo;
#endif
