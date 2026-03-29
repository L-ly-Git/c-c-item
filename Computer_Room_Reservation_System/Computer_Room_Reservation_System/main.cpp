#include "system.h"

int main() {
	int choice = -1;
	System s;

	while (choice!=0) {
		s.menu();
		cout << "请输入你的选择:";
		cin >> choice;
		
		switch (choice) {
		case 1:
			//学生操作系统函数
		{
			Stu_System stu_s(s);
			stu_s.sys_stu();
			stu_s.save_Student(s);
		}
			break;
		case 2:
		{//老师操作系统函数
			Teacher_System teacher_s(s);
			teacher_s.sys_teacher();
			teacher_s.save_Teacher(s);
		}
			break;
		case 3:
			//管理员操作系统
		{
			Admin_System admin_s(s);
			admin_s.sys_admin();
			admin_s.save_Admin(s);
		}
			break;
		case 0:
			s.save();
			cout << "已经退出系统" << endl;
			break;
		default:
			break;
		}
		system("pause");
		system("cls");
	}

	return 0;
}