#include "system.h"

Admin_System::Admin_System(const System& s) {
	this->m_Admins = s.m_Admins;
	this->m_Rooms = s.m_Rooms;
	this->m_Stus = s.m_Stus;
	this->m_Teachers = s.m_Teachers;
}

bool Admin_System::sys_in_Admin() {
	string name;
	string id;
	string password;

	cout << "输入管理员姓名:";
	cin >> name;
	cout << "输入密码";
	cin >> password;
	Admin a(name, password);
	if (find(this->m_Admins.begin(), this->m_Admins.end(), a) != this->m_Admins.end()) {
		cout << "登录成功" << endl;
		return true;
	}
	else {
		cout << "登录失败，请重新选择" << endl;
		return false;
	}
}

//菜单
void Admin_System::Admin_menu() {
	cout << "==========管理员子系统==========" << endl;
	cout << "==========1.查看学生信息========" << endl;
	cout << "==========2.查看教师信息========" << endl;
	cout << "==========3.查看预约信息========" << endl;
	cout << "==========4.增加人员信息========" << endl;
	cout << "==========5.删除人员信息========" << endl;
	cout << "==========6.清空预约信息========" << endl;
	cout << "==========0.返回主系统==========" << endl;
}

//查看学生类
void Admin_System::show_Student() {
	for (vector<Student>::iterator it = this->m_Stus.begin(); it != this->m_Stus.end(); it++) {
		cout << it->m_Id << " " << it->m_Name << endl;
	}
}

//查看教师类
void Admin_System::show_Teacher() {
	for (vector<Teacher>::iterator it = this->m_Teachers.begin(); it != this->m_Teachers.end(); it++) {
		cout << it->m_Id << " " << it->m_Name << endl;
	}
}

//添加人员
void Admin_System::Add_Person() {
	int choice = -1;
	int num;
	cout << "选择增加人数:";
	cin >> num;
	while (num>0) {
		cout << "请选择增加人员身份：教师(1),学生(2) ,退出(0)" << endl;
		cin >> choice;
		string id;
		string name;
		string password = "000000";//使用默认密码
		if (choice == 0) {
			return;
		}
		cout << "输入id:";
		cin >> id;
		cout << "输入名字:";
		cin >> name;
		switch (choice) {
		case 1:
		{
			Teacher t(id, name, password);
			this->m_Teachers.push_back(t);
			num--;
			break;
		}
		case 2:
		{
			Student stu(id, name, password);
			this->m_Stus.push_back(stu);
			num--;
			break;
		}
		case 0:
			cout << "退出" << endl;
			break;
		default:
			cout << "输入错误，请重新选择" << endl;
			break;
		}
	}

}

//删除人员
void Admin_System::Del_Person() {
	int choice = -1;
	int num;
	cout << "选择删除人数:";
	cin >> num;
	while (num > 0) {
		cout << "请选择删除人员身份：学生(1),教师(2),退出(0)" << endl;
		cin >> choice;
		string id;
		string name;
		if (choice == 0) {
			return;
		}
		cout << "输入id:";
		cin >> id;
		cout << "输入名字:";
		cin >> name;
		switch (choice) {
		case 1:
		{
			int flag = 0;
			if (this->m_Stus.size() == 0) {
				cout << "学生人员信息为空" << endl;
				break;
			}
			for (vector<Student>::iterator it = this->m_Stus.begin(); it != this->m_Stus.end(); it++) {
				if ((*it).m_Id == id && (*it).m_Name == name) {
					cout << (*it).m_Id << " " << (*it).m_Name << " " << (*it).m_Password << endl;
					cout << "是否删除:1(是),0(否)";
					int chooce;
					cin >> chooce;
					if (chooce) {
						vector<Student>::iterator del_it = it;
						this->m_Stus.erase(del_it);
						flag = 1;
					}
					break;
				}
			}
			if (!flag) {
				cout << "未找到对应人员信息" << endl;
			}
			num--;
			break;
		}
		case 2:
		{
			int flag = 0;
			if (this->m_Teachers.size() == 0) {
				cout << "教师人员信息为空" << endl;
				break;
			}
			for (vector<Teacher>::iterator it = this->m_Teachers.begin(); it != this->m_Teachers.end(); it++) {
				if ((*it).m_Id == id && (*it).m_Name == name) {
					cout << (*it).m_Id << " " << (*it).m_Name << " " << (*it).m_Password << endl;
					cout << "是否删除:1(是),0(否)";
					int chooce;
					cin >> chooce;
					if (chooce) {
						vector<Teacher>::iterator del_it = it;
						this->m_Teachers.erase(del_it);
						flag = 1;
					}
					break;
				}
			}
			if (!flag) {
				cout << "未找到对应人员信息" << endl;
			}
			num--;
			break;
		}
		case 0:
			cout << "退出" << endl;
			break;
		default:
			cout << "输入错误，请重新选择" << endl;
			break;
		}
	}
}

//查看预约信息和当前机房状态
void Admin_System::show_log() {
	
	
	cout << "机房情况" << endl;
	ifstream ifs;
	ifs.open(Room_File, ios::in);
	if (!ifs.is_open()) {
		cout << "文件打开失败" << endl;
		return;
	}
	string data;
	while (ifs >> data) {
		vector<string> res = this->split(data, ',');
		cout << "机房" << res[0] << " 容量" << res[1] << endl;
	}
	ifs.close();
	cout << "预约情况" << endl;
	this->reservation_info();
}

//情空当前预约情况
void Admin_System::clear_log() {
	int sum = 0;
	for (int i = 0; i < room_num; i++) {
		sum += this->m_Rooms[i].m_Res.size();
	}
	if (sum == 0) {
		cout << "预约情况为空" << endl;
		return;
	}
	cout << "预约情况" << endl;
	this->reservation_info();
	cout << "是否确定情空：是(1),否(0):";
	int choice;
	cin >> choice;
	if (choice) {
		for (int i = 0; i < room_num; i++) {
			this->m_Rooms[i].m_Res.clear();
		}
	}
}

void Admin_System::sys_admin() {
	if (this->sys_in_Admin()) {
		int choice = -1;
		while (choice) {
			this->Admin_menu();
			cout << "请输入选择:";
			cin >> choice;

			switch (choice) {
			case 1: 
				this->show_Student();
				break;
			case 2:
				this->show_Teacher();
				break;
			case 3:
				this->show_log();
				break;
			case 4:
				this->Add_Person();
				break;
			case 5:
				this->Del_Person();
				break;
			case 6:
				this->clear_log();
				break;
			case 0:
				cout << "退出管理员子系统,返回主系统" << endl;
				return;
			default:
				cout << "输入错误，请重新给输入" << endl;
				break;
			}
			system("pause");
			system("cls");
		}
	}
	else {
		return;
	}

} //管理元系统整体操作


void Admin_System::save_Admin(System& s) {
	s.m_Admins = this->m_Admins;
	s.m_Rooms = this->m_Rooms;
	s.m_Stus = this->m_Stus;
	s.m_Teachers = this->m_Teachers;
}