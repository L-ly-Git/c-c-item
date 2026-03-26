#include "System.h"

int main()
{

	srand((unsigned int)time(NULL));
	
	System s;
	int choice = 0;
	while (true) {
		s.menu();
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "==========开始比赛==========" << endl;
			s.contest_All();
			break;
		case 2:
			cout << "===========开始比赛=========" << endl;
			s.init(); //重新初始化
			s.contest_All();
			break;
		case 3:
			s.out_csv();
			break;
		case 4:
			s.cls_csv();
			break;
		case 0:
			cout << "欢迎再次使用" << endl;
			system("pause");
			return 0;
		default:
			cout << "请重新输入选项" << endl;
			break;
		}
		system("pause");
		system("cls");
	}
	
	return 0;
}