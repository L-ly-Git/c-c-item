#include "system.h"

Teacher_System::Teacher_System(const System& s) {
	this->m_Teachers = s.m_Teachers;
	this->m_Rooms = s.m_Rooms;
}

bool Teacher_System::sys_in_Teacher() {
	string name;
	string id;
	string password;

	cout << "输入教师姓名:";
	cin >> name;
	cout << "输入教师id:";
	cin >> id;
	cout << "输入密码";
	cin >> password;
	Teacher t(id, name, password);
	if (find(this->m_Teachers.begin(), this->m_Teachers.end(), t) != this->m_Teachers.end()) {
		cout << "登录成功" << endl;
		return true;
	}
	else {
		cout << "登录失败，请重新选择" << endl;
		return false;
	}

}
//菜单
void Teacher_System::teacher_menu() {
	cout << "==========教师子系统==========" << endl;
	cout << "====1.查看所有预约信息========" << endl;
	cout << "====2.进行审核================" << endl;
	cout << "====0.返回主系统==============" << endl;
}

//查看所有预约情况 

//进行审核
void Teacher_System::check() {
	int sum = 0;
	vector<vector<int>> room_res_idx; //存储需要审核的预约的机房和预约在机房中的位置
	for (int i = 0; i < room_num; i++) {
		int res_idx = 0;
		for (vector<Reservation>::iterator it = this->m_Rooms[i].m_Res.begin(); it != this->m_Rooms[i].m_Res.end(); it++) {
			if (it->m_Situation == "审核中") {
				sum++;
				cout <<sum<<". "<< it->roomname << " " << it->m_Name << " " << it->m_Id << " 星期" << it->m_Date << " " << it->m_Situation << endl;
				room_res_idx.push_back({ i,res_idx }); //存储需要审核的预约的机房和预约在机房中的位置
			}
			res_idx++;
		}
	}
	if (sum == 0) {
		cout << "没有需要审核的预约" << endl;
		return;
	}

	int choice = -1;
	int temp_res = sum; //记录需要审核的预约总数，后续每审核一个预约就减1，直到所有预约审核完成或者教师选择退出审核操作
	while (choice != 0) {
		if (temp_res == 0) {
			cout << "所有预约已经审核完成" << endl;
			return;
		}
		cout << "输入要审核的预约编号(输入0退出):";
		cin >> choice;
		if(choice==0){
			cout << "退出审核操作" << endl;
			return;
		}
		else if (choice > sum) {
			cout << "输入错误，请重新选择" << endl;
		}
		else {
			int room_idx = room_res_idx[choice - 1][0];
			int res_idx = room_res_idx[choice - 1][1];
			cout << "是否通过审核:1(通过),0(不通过):";
			int choice_temp = -1;
			cin >> choice_temp;
			if (choice_temp) {
				this->m_Rooms[room_idx].m_Res[res_idx].m_Situation = "审核通过";
			}
			else {
				this->m_Rooms[room_idx].m_Res[res_idx].m_Situation = "审核未通过";
			}
			temp_res--;
		}
	}

}

void Teacher_System::sys_teacher() {
	if (this->sys_in_Teacher()) {
		int choice = -1;
		while (choice != 0) {
			this->teacher_menu();
			cout << "请输入选择:";
			cin >> choice;
			switch (choice) {
			case 1:
				this->reservation_info();
				break;
			case 2:
				this->check();
				break;
			case 0:
				cout << "退出教师子系统,返回主系统" << endl;
				return;
			default:
				cout << "输入错误，请重新选择" << endl;
				break;
			}
			system("pause");
			system("cls");
		}
	}
	else {
		return;
	}
} //教师系统整体操作

void Teacher_System::save_Teacher(System& s){
	s.m_Rooms = this->m_Rooms;
}