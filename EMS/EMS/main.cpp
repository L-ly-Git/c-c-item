#include "EMS.h"


void test() {
	WorkerManage WM;
	//功能选择
	int choice = 0;
	while (true) {
		WM.Menu();
		cout << "请输入你的选择" << endl;
		cin >> choice;

		switch (choice)
		{
		case 0:
			WM.exit_sys();
			break;
		case 1:
			WM.AddWorker();
			break;
		case 2:
			WM.OutWorker();
			break;
		case 3:
			WM.DelWorker();
			break;
		case 4:
			WM.ChangeWorker();
			break;
		case 5:
			WM.FindWorker();
			break;
		case 6:
			WM.SortWorker();
			break;
		case 7:
			WM.ClearWorker();
			break;
		case 8:
			WM.save();
			break;
		default:
			system("cls");
			break;
		}

		system("pause");
		system("cls");
	}
	


}

int main() {
	test();

	system("pause");

	return 0;

}