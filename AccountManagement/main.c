#define _CRT_SECURE_NO_WARNINGS//����scanf��unsafe����
#include <stdio.h>
#include <stdlib.h>
#include"menu.h" //ͷ�ļ�����
int main()
{
	int choose; //�˵�ѡ����Ŀ
	printf("��ӭʹ�üƷѹ���ϵͳ������\n");
	do {
		system("cls"); //�����Ļ
		outputMenu();  //����˵�
		choose = -1;
		scanf("%d", &choose);
		fflush(stdin);
		rewind(stdin); //�������
		switch (choose)
		{
		case 0: {
			printf("-----��лʹ�üƷѹ���ϵͳ��ϵͳ���˳���-----\n");
			ExitSystem();
			exit(0); //�˳�ϵͳ
            break;
		}
		case 1: {
			printf("-----------��ӿ�-----------\n");
			addCard();
			system("pause"); //�ȴ��û��ź�
			break;
		}
		case 2: {
			printf("-----------��ѯ��-----------\n");
			query();
			system("pause");
			break;
		}
		case 3: {
			printf("-----�ϻ�-----\n"); 
			logon();
			system("pause");
			break;
		}
		case 4: {
			printf("-----�»�-----\n"); 
			settle();
			system("pause");
			break;
		}
		case 5: {
			printf("-----��ֵ-----\n");
			addMoney();
			system("pause");
			break;
		}
		case 6: {
			printf("-----�˷�-----\n");
			refundMoney();
			system("pause");
			break;
		}
		case 7: {
			printf("-----��ѯͳ��-----\n");
			collectInfo();
			system("pause");
			break;
		}
		case 8: {
			printf("-----ע����-----\n"); 
			annul();
			system("pause");
			break;
		}
		default:
		{
			printf("�����������󣡴˴���֧�������0��8�����֣������Ƿ���˵���Ӧ���������룡\n");
			system("pause");
		}
		}  //switch����
	} while (1);
	return 0;
}  //main
