#ifndef MODEL_H
#define MODEL_H //����ͷ�ļ����ظ�����

#include< time.h>
typedef struct Card
{
	char Number[18];  //�˺�
	char Password[8]; //����
	int  Status;      //��״̬��0Ϊδ�ϻ���1Ϊ���ϻ���2Ϊ����ע����3Ϊ����ʧЧ��
	time_t  Start;       //����ʱ��
	time_t  End;         //���Ľ�ֹʱ��
	float   fTotalUse;     //�ۼƽ��
	time_t    LastTime;        //����ʱ��
	int       UseCount;  //�ܼ�ʹ�ô���
	float     Balance;      //���
	int       Delete;            //ɾ����ʶ��0Ϊδɾ����1Ϊ��ɾ��
}Card;
typedef struct CardNode
{
	Card data; //������
	struct CardNode* next;//ָ����
}CardNode, * lpCardNode;
//������Ϣ�ṹ��
typedef struct Billing {

	char aCardName[18];  //����
	time_t tStart;       //�ϻ�ʱ��
	time_t tEnd;         //�»�ʱ��
	float fAmount;       //���ѽ��
	int nStatus;         //����״̬��0-δ���㣬1-�ѽ���
	int nDel;            //ɾ����ʶ��0-δɾ����1-��ɾ��
}Billing;
typedef struct LogonInfo {
	char aCardName[18];   //�ϻ�����
	time_t tLogon;        //�ϻ�ʱ��
	float fBalance;       //�ϻ�ʱ������
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
//��ֵ�˷ѽṹ��
typedef struct Money {
	char cardname[18];
	time_t tTime;
	int nStatus;//��ֵ״̬  0 ��ֵ  1�˷�
	float fMoney;
	int nDel;//ɾ����־  0δɾ��  1ɾ��
}Money;
typedef struct MoneyInfo
{
	char cardname[18];
	float fMoney;
	float fBalance;
}MoneyInfo;
#endif
