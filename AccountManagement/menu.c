#define _CRT_SECURE_NO_WARNINGS//����scanf��unsafe����
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
 //ͷ�ļ�����
void mainMenu()
{
	printf("***********��ӭ�������ɹ���ϵͳ************\n");
	printf("1.��ͨ����Ա����\n");
	printf("2.��������Ա����\n");
	printf("0.�˳�\n");
}
void manageMenu()
{
	printf("��ӭ���볬������Ա����\n");
	printf("1.ɾ�����û�\n");
	printf("2.�޸ļƷ���Ϣ\n");
	printf("0.�˳�\n");

}
void outputMenu()    //չʾ�˵�
{
	printf("-----��ӭʹ�üƷѹ���ϵͳ-----\n");
	printf("---�˵�---\n");
	printf("1.��ӿ�\n");
	printf("2.��ѯ��\n");
	printf("3.�ϻ�\n");
	printf("4.�»�\n");
	printf("5.��ֵ\n");
	printf("6.�˷�\n");
	printf("7.��ѯͳ��\n");
	printf("8.ע����\n");
	printf("9.����\n");
	printf("0.�˳�ϵͳ\n");
	printf("�����������Ĺ��ܣ�����0��8������ѡ���Ӧ����:\n");

}
void addCard() //���
{
	Card card; 
	Card *p=NULL;
	char number[30];    //�û���
	char password[20]; //����
	char password2[20]; //ȷ������
	struct tm* endTime; //��ֹʱ��
	struct tm* startTime; //��ʼʱ��
	int queren = 1;  //ȷ�������־
	printf("������18λ�ڵĿ��ţ�");
	scanf("%s", number);
	if (strlen(number) > 18 )//����18λ
	{
	printf("���Ž�����1-18λ�������²�����\n");
	return;
	}
	if (queryCardInfo(number,&p) != NULL)  //�����ظ�
	{
		printf("�ÿ����Ѵ��ڣ������²�����\n");
		return;
	}
	 strcpy(card.Number, number); //���Ŵ���
		
			printf("����������(����Ϊ1-8λ):\n");
			scanf("%s", password);
			if (strlen(password) > 8) {
				printf("���볬��8λ����������������(����Ϊ1-8λ):\n");
				scanf("%s", password);
			}
			printf("��ȷ������(����Ϊ1-8λ):\n");
			
			while (queren) {
				scanf("%s", password2);
                if (strcmp(password, password2)) {
				printf("�������벻һ�£�������ȷ������(����Ϊ1-8λ):\n");
				
				}
				else {
					queren = 0;
				}
			}
	strcpy(card.Password, password); //�������
	printf("�����뿨�ڽ�");
		scanf("%f", & card.Balance);
		//����ʼ��
		card.fTotalUse = card.Balance; //��ʼ�ܽ��
		card.Delete = 0;//δɾ��
		card.Status = 0;//��ʼ״̬Ϊδ�ϻ�
		card.UseCount = 0; //��ʼʹ�ô���Ϊ0
		card.Start = card.End = card.LastTime = time(NULL); //�ӵ�ǰ��ʼ����ʱ��
		startTime = localtime( & card.Start);
		endTime = localtime(&card.End);   //ʱ��ת��
		endTime->tm_year = startTime->tm_year + 1;  //��Ч��Ϊ1��
		card.End = mktime(endTime);   //ʱ��ת��

		printf("----------------------------��ӿ�����Ϣ----------------------------\n");
		printf("   �˿�����     �˿�����    ��ǰ״̬   �������\n");

		printf("   %s          %s            %d      %f\n", card.Number, card.Password, card.Status, card.Balance);
		if (FALSE == addCardInfo(card))
			printf("-----��Ǹ�������ʧ�ܣ�-----\n");
	  else  printf("-----��ϲ������ӳɹ���-----\n");
		/*���������˵�*/
		int t;
		printf("--------��ѡ�����������Ĳ���--------\n");
		printf("����1��������ӿ�\n");
		printf("�����������ص����˵�\n");
		scanf("%d", &t);
		fflush(stdin);
		rewind(stdin); //���������
		switch (t) {
		case 1: //�������
		{
			addCard(); 
			break;
		}
		default:  //���˵�
		{
			break;
		}
		} //switch
} //����
void query()  //��ѯ����Ϣ
{
	char num[20]; //����
	Card* pCard = NULL;
	char aLastTime[20]; //ʱ��
	int length = 0;  //Ҫ��ʾ�ĸ���
	int way = 0;  //��ѯ��ʽ
	int i,j; //ѭ��
	int cardstore = getCardCount_binary(CARDPATHBINARY);//�洢��������
	printf("����Ϊ�ɹ�ѡ��Ĳ�ѯ��ʽ��\n");
	printf("1��  ��ȷ��ѯ\n");
	printf("2��  ģ����ѯ\n");
	printf("����:չʾ�����û���Ϣ\n");
	scanf("%d", &way);
	
	if (way == 1)  //��ȷ��ѯ
	{
		printf("�����뿨��(����1-18):\n");
		scanf("%s", num);
		pCard = (Card *)malloc(sizeof(Card));

		queryCardInfo(num,&pCard);
		if (strcmp(pCard->Number,num)!=0)
		{
			printf("����ѯ�Ŀ��Ų����ڣ�\n");
		}
		else
		{
		
		printf("----------------------------����Ϊ�ÿ���Ϣ----------------------------\n");
		printf("   �˿�����    ��ǰ״̬   ��ǰ���         �ۼƽ��     ʹ�ô���       �ϴ�ʹ��ʱ��\n");
		char lasttime[20];
		timeToString(pCard->LastTime, lasttime);
        printf("   %s         %d       %f      %f         %d     %s\n", pCard->Number, pCard->Status, pCard->Balance, pCard->fTotalUse, pCard->UseCount,lasttime);
		}
	}
	else if (way == 2) //ģ����ѯ
	{
		printf("������ģ����ѯ�Ĺؼ���(����1-18):\n");
		scanf("%s", num);
		pCard=QueryCards(num, &length);
		if ((length)== 0)
		{
			printf("����ѯ�Ŀ��Ų����ڣ�\n");
		}
		else {
			printf("-----------------------����Ϊģ����ѯ������������ݿ���Ϣ-----------------------\n");
			printf("   �˿�����    ��ǰ״̬   ��ǰ���         �ۼƽ��     ʹ�ô���       �ϴ�ʹ��ʱ��\n");
			for (i = 0; i < length; i++)
			{
				timeToString(pCard[i].LastTime, aLastTime); //ʱ��ת��
				printf("   %s         %d       %f      %f         %d     %s\n", pCard[i].Number, pCard[i].Status, pCard[i].Balance, pCard[i].fTotalUse, pCard[i].UseCount, aLastTime);
			} //for
			free(pCard);
		} //else
	} //if
	else //չʾ������Ϣ
	{
		pCard = AllCards(&cardstore);
			printf("-----------------------����Ϊ��ǰϵͳ�����п�����Ϣ-----------------------\n");
			printf("   �˿�����    ��ǰ״̬   ��ǰ���         �ۼƽ��     ʹ�ô���       �ϴ�ʹ��ʱ��\n");
			for (i = 0; i < cardstore; i++)
			{
				timeToString(pCard[i].LastTime, aLastTime);  //ʱ��ת��
				printf("   %s         %d       %f      %f         %d     %s\n", pCard[i].Number, pCard[i].Status, pCard[i].Balance, pCard[i].fTotalUse, pCard[i].UseCount, aLastTime);
			}
			free(pCard);
	}
	pCard = NULL;
	int t;
	/*���������˵�*/
	printf("--------��ѡ�����������Ĳ���--------\n");
	printf("����1��������ѯ����Ϣ\n");
	printf("�����������ص����˵�\n");
	scanf("%d", &t);
	fflush(stdin);
	rewind(stdin);
	switch (t) {
	case 1: //������ѯ 
	{
		query(); 
		break;
	}
	default:  //���˵�
	{
		break;
	}
	} //switch
} //����
void logon()
{
	char aName[30] = {0};
	char aPwd[20] = {0};
	Card* pCard = NULL;
	char aLastTime[30];
	LogonInfo* pInfo = NULL;
	int nResult = 0;
	printf("�������ϻ��Ŀ��ţ�\n");
	scanf("%s",aName);
	if (strlen(aName) > 18)   //����18λ
	{
		printf("���Ž�����1-18λ�������²�����\n");
		return;
	}
	printf("�������ϻ��������룺\n");
	scanf("%s", aPwd);
	pInfo = (LogonInfo*)malloc(sizeof(LogonInfo));
	nResult = doLogon(aName,aPwd,pInfo);
	switch (nResult) {
	case 0:
		printf("---------�ϻ�ʧ�ܣ�---------\n");
		break;
	case 1:
		printf("--------�ϻ��Ŀ���Ϣ����-----------\n");
		printf("   ����       ���         �ϻ�ʱ��     \n");
		timeToString(pInfo->tLogon,aLastTime);
		printf("    %s          %f           %s\n", pInfo->aCardName, pInfo->fBalance, aLastTime);
		printf("-------�ϻ��ɹ�!---------\n");break;
	case 2:
		printf("----------�ÿ�����ʹ��!-------\n");break;
	case 3:
		printf("----------����!----------\n");break;
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
	printf("�������»����ţ�����1-18��");
	scanf("%s",aName);
	printf("�������»����루����1-8��");
	scanf("%s",aPwd);
	nResult = doSettle(aName,aPwd,pInfo);
	printf("\n");
	printf("--------------�»���Ϣ����-----------\n");
	switch (nResult) {
	case 0:
	{
		printf("�»�ʧ��!\n");
		break;
	}
	case 1: {  
		printf("����            ����             ���              �ϻ�ʱ��             �»�ʱ��\n");
		timeToString(pInfo->tStart,aStartTime);
		timeToString(pInfo->tEnd,aEndTime);
		printf("%s        %f         %f        %s         %s\n",pInfo->aCardName,pInfo->fAmount,pInfo->fBalance,aStartTime,aEndTime);
		printf("------------�»��ɹ�----------\n");
		break;
	}
	case 2: {
		printf("�ÿ�δ��ʹ��\n");
		break;
	}
	case 3:{
		printf("������\n");
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

	printf("�������ֵ���ţ�����1-18��");
	scanf("%s", aName);
	printf("�������ֵ�����루����1-8��");
	scanf("%s", aPwd);
	printf("�������ֵ���:");
	scanf("%f", &fAmount);
	strcpy(Minfo.cardname, aName);
	Minfo.fMoney = fAmount;
	nResult = doAddMoney(aName, aPwd, &Minfo);
	

	if (nResult == 1)
	{
		printf("\n");
		printf("--------------��ֵ��Ϣ����-----------\n");
		printf("����\t��ֵ���\t���\n");
		printf("%s\t%f\t%f\t\n", Minfo.cardname, Minfo.fMoney, Minfo.fBalance);
	}
	else
	{
		printf("----------------��ֵʧ��----------------\n");
	}
}
void refundMoney()
{
	char aName[18] = { 0 };
	char aPwd[8] = { 0 };
	MoneyInfo Minfo;
	int nResult = -1;

	printf("�������˷ѿ��ţ�����1-18��");
	scanf("%s", aName);
	printf("�������˷ѿ����루����1-8��");
	scanf("%s", aPwd);
	strcpy(Minfo.cardname, aName);
	nResult = doRefoundMoney(aName, aPwd, &Minfo);
	switch (nResult)
	{
	case 0:
	{
		printf("********�˷�ʧ�ܣ�***********\n");
		break;
	}
	case 1:
	{
		printf("\n");
		printf("--------------�˷���Ϣ����-----------\n");
		printf("����\t�˷ѽ��\t���\n");
		printf("%s\t%f\t%f\t\n", Minfo.cardname, Minfo.fMoney, Minfo.fBalance);
		break;
	}
	case 2:
	{
		printf("**************�˿��Ѿ�ע��***************\n");
		break;
	}
	case 3:
	{
		printf("**************�˿�����***************\n");
		break;
	}
	default:
		break;
	}

	
}
void annul()
{
	Card p;
	printf("�������˷ѿ��ţ�����1-18��");
	scanf("%s", p.Number);
	printf("�������˷ѿ����루����1-8��");
	scanf("%s", p.Password);
	if (FALSE == annulCard(&p))
	{
		printf("ע��ʧ��!\n");
	}
	else
	{
		printf("**********ע����Ϣ����************\n");
		printf("����\t�˿���\n");
		printf("%s\t%f", p.Number, p.Balance);
	}
}
void collectInfo()
{
	printf("***************��ѯͳ��*****************\n");
	printf("1.ע������Ϣ��ʾ\n2.���п���Ϣ�Լ������ܶ�\n3.��ֵ�˷���Ϣ��ʾ\n4.���»���Ϣ��ʾ\n0.�˳�\n");
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

//����Ա����
int delete_card()
{
	Card *pCard = NULL;
	int ncount = 0;
	char name[18];
	char aLastTime[20]; //ʱ��
	int cardstore = getCardCount_binary(CARDPATHBINARY);//�洢��������
	pCard = AllCards(&cardstore);
	if (pCard == NULL)
	{
		printf("û�п��ţ��޷�ɾ����");
		return 0;
	}
	printf("-----------------------����Ϊ��ǰϵͳ�����п�����Ϣ-----------------------\n");
	printf("   �˿�����    ��ǰ״̬   ��ǰ���         �ۼƽ��     ʹ�ô���       �ϴ�ʹ��ʱ��\n");
	for (int i = 0; i < cardstore; i++)
	{
		timeToString(pCard[i].LastTime, aLastTime);  //ʱ��ת��
		printf("   %s         %d       %f      %f         %d     %s\n", pCard[i].Number, pCard[i].Status, pCard[i].Balance, pCard[i].fTotalUse, pCard[i].UseCount, aLastTime);
	}
	printf("����ɾ�����ţ�");
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
		printf("�˿���û�»���ɾ��ʧ�ܣ�\n");
		return 0;
	}
	else if (ncount == cardstore)
	{
		printf("���Ҳ����˿���ɾ��ʧ��!\n");
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
			printf("�ļ���ʧ��!");
			return 0;
		}
		else
		{

			fwrite(pCard, sizeof(Card), cardstore - 1, fp);
			printf("ɾ���ɹ�!!!\n");
			fclose(fp);
			return 1;
		}
	}
}
void update_charge()
{
	int unit=0;
	float charge = 0;
	printf("����Ʒѵ�Ԫ��");
	scanf("%d", &unit);
	printf("����Ʒѵ��ۣ�");
	scanf("%f", &charge);
	if (charge < 0 || unit < 0)
	{
		printf("���벻��С��0��");
		return;
	}
	else
	{
		FILE * fp = fopen(CHARGEPATH, "w+");
		fprintf(fp, "%d %f", unit, charge);
		printf("�޸ĳɹ���");
		fclose(fp);
	}
}