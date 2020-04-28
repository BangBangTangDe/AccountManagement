#define _CRT_SECURE_NO_WARNINGS//消除scanf的unsafe报错
#include <stdio.h>
#include <stdlib.h>
#include"menu.h" //头文件引入
int main()
{
	int choose; //菜单选择项目
	int choose1;
	char id[18];
	char pwd[18];
	do {
		system("cls");
		mainMenu();
		scanf("%d", &choose1);
		if (choose1 == 1)
		{
			system("cls");
			printf("欢迎使用计费管理系统！！！\n");
			do {
				system("cls"); //清除屏幕
				outputMenu();  //输出菜单
				choose = -1;
				scanf("%d", &choose);
				fflush(stdin);
				rewind(stdin); //清除缓存
				switch (choose)
				{
				case 0: {
					printf("-----感谢使用计费管理系统，系统已退出！-----\n");
					ExitSystem();
					exit(0); //退出系统
					break;
				}
				case 1: {
					printf("-----------添加卡-----------\n");
					addCard();
					system("pause"); //等待用户信号
					break;
				}
				case 2: {
					printf("-----------查询卡-----------\n");
					query();
					system("pause");
					break;
				}
				case 3: {
					printf("-----上机-----\n");
					logon();
					system("pause");
					break;
				}
				case 4: {
					printf("-----下机-----\n");
					settle();
					system("pause");
					break;
				}
				case 5: {
					printf("-----充值-----\n");
					addMoney();
					system("pause");
					break;
				}
				case 6: {
					printf("-----退费-----\n");
					refundMoney();
					system("pause");
					break;
				}
				case 7: {
					printf("-----查询统计-----\n");
					collectInfo();
					system("pause");
					break;
				}
				case 8: {
					printf("-----注销卡-----\n");
					annul();
					system("pause");
					break;
				}
				case 9:break;

				default:
				{
					printf("输入内容有误！此处仅支持输入从0到8的数字，请检查是否与菜单对应后重新输入！\n");
					system("pause");
				}
				}  //switch括号
			} while (choose!=9);
		}
		else if (choose1 == 2)
		{
			printf("输入账号：\n");
			scanf("%s", id);
			printf("输入密码：\n");
			scanf("%s", pwd);
			if (strcmp(id, "root") == 0 && strcmp(pwd, "root") == 0)
			{
				system("cls");
				int choice = 0;
				do {
					system("cls");
					manageMenu();
					scanf("%d", &choice);
					if (choice == 1)
					{
						delete_card();
						system("pause");
					}
					else if (choice == 2)
					{
						update_charge();
						system("pause");
					}
				} while (choice != 0);
			}
			else
			{
				
				printf("输入账号密码错误!!!\n");
				system("pause");
			}
		}
	} while (choose1 != 0);
	return 0;
}  //main
