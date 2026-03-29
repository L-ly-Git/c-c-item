#include "system.h"

Stu_System::Stu_System(const System& s) {
	this->m_Rooms = s.m_Rooms;
	this->m_Stus = s.m_Stus;
}

bool Stu_System::sys_in_Stu(const Student& stu) {

	if (find(this->m_Stus.begin(), this->m_Stus.end(), stu) != this->m_Stus.end()) {
			cout << "登录成功" << endl;
			return true;
	}
	else {
		cout << "登录失败，请重新选择" << endl;
		return false;
	}
}

//菜单
void Stu_System::student_menu() {
	cout << "==========学生子系统==========" << endl;
	cout << "====1.查看所有预约信息========" << endl;
	cout << "====2.查看个人预约信息========" << endl;
	cout << "====3.进行预约================" << endl;
	cout << "====4.取消预约================" << endl;
	cout << "====0.返回主系统==============" << endl;
}

//查看所有预约情况 

//查看预约信息
void Stu_System::show_log_info(const Student& stu) {
	int sum = 0;
	for (int i = 0; i < room_num; i++) {
		for (vector<Reservation>::iterator it = this->m_Rooms[i].m_Res.begin(); it != this->m_Rooms[i].m_Res.end(); it++) {
			if (it->m_Id == stu.m_Id) {
				sum++;
				cout << it->roomname << " 星期" << it->m_Date << " " << it->m_Situation << endl;
			}
		}
	}
	if (sum == 0) {
		cout << "你的预约情况未空" << endl;
	}
}

//进行预约

void Stu_System::reservate(const Student& stu) {
	//机房情况
	cout << "机房情况:" << endl;
	ifstream ifs;
	ifs.open(Room_File, ios::in);
	if (!ifs.is_open()) {
		cout << Room_File<<"文件打开失败" << endl;
		return;
	}
	else {
		string data;
		while (ifs >> data) {
			vector<string> res = this->split(data, ',');
			cout << "机房" << res[0] << " 容量" << res[1] << endl;
		}
	}
	ifs.close();
	//进行预约
	int room_choice = 0;
	cout << "请选择你要预约的机房:(输入机房后的数字编号,例如机房1输入1):";
	cin >> room_choice;
	string roomname = "机房" + to_string(room_choice); // 机房名
	string date; //预约日期，输入星期几(1,2,...)
	//先输入预约日期，判断是否还有容量
	cout << "请输入预约日期:星期(输入数字:1,2,3,4，...)";
	cin >> date;
	int date_int = stoi(date);
	if (date_int > 0 && date_int < 8) {
		if (this->m_Rooms[room_choice - 1].m_size[date_int - 1] == this->m_Rooms[room_choice - 1].m_capicity) {		
			cout << "星期" << date << "当前机房已经满了，无法继续预约" << endl;
			return;
		}

		//预约成功，更新机房预约情况		
		this->m_Rooms[room_choice - 1].m_size[date_int - 1]++;
		Reservation res(roomname, stu.m_Name, stu.m_Id, date, "审核中");
		this->m_Rooms[room_choice - 1].m_Res.push_back(res);		
		cout << "预约成功，等待审核" << endl;
		}



}

//取消预约
void Stu_System::change_reservation(const Student& stu) {
	//先展示个人预约情况
	vector<Reservation> res_vec; //存储个人预约情况
	vector<vector<int>> room_res_idx; //存储个人预约的机房和预约在机房中的位置
	int sum = 0;
	for (int i = 0; i < room_num; i++) {
		int res_idx = 0;
		for (vector<Reservation>::iterator it = this->m_Rooms[i].m_Res.begin(); it != this->m_Rooms[i].m_Res.end(); it++) {
			if (it->m_Id == stu.m_Id && it->m_Situation!="取消预约"&&it->m_Situation!="审核未通过") {
				sum++;
				cout <<sum <<". " << it->roomname << " 星期" << it->m_Date << " " << it->m_Situation << endl;
				Reservation res(it->roomname, it->m_Name, it->m_Id, it->m_Date, it->m_Situation);
				res_vec.push_back(res);
				room_res_idx.push_back({i,res_idx}); //存储个人预约的机房和预约在机房中的位置
			}
			res_idx++;
		}
		
	}
	if (sum == 0) {
		cout << "你的预约情况未空" << endl;
	}
	int choice = -1;
	while (choice != 0) {
		cout << "请输入你要取消的预约编号(输入0退出):";
		cin >> choice;
		if (choice == 0) {
			cout << "退出取消预约操作" << endl;
			return;
		}
		else if (choice > sum) {
			cout << "选择错误，请重新选择" << endl;

		}
		else {
			int room_idx = room_res_idx[choice - 1][0];//机房编号
			int res_idx = room_res_idx[choice - 1][1]; //预约编号
			this->m_Rooms[room_idx].m_Res[res_idx].m_Situation = "取消预约";
		}
	}


}

void Stu_System::sys_stu() {
	string name;
	string id;
	string password;

	cout << "输入学生姓名:";
	cin >> name;
	cout << "输入学生id:";
	cin >> id;
	cout << "输入密码";
	cin >> password;
	Student stu(id, name, password);
	if (this->sys_in_Stu(stu)) {
		int choice = -1;
		while (choice != 0) {
			this->student_menu();
			cout << "请输入选择:";
			cin >> choice;
			
			switch (choice) {
			case 1:
				this->reservation_info();
				break;
			case 2:
				this->show_log_info(stu);
				break;
			case 3:
				this->reservate(stu);
				break;
			case 4:
				this->change_reservation(stu);
				break;
			case 0:
				cout << "退出学生子系统，返回主系统" << endl;
				return;
			default:
				cout << "请输入正确的选型" << endl;
				break;
			}

			system("pause");
			system("cls");
		}
	}


} //学生系统整体操作



void Stu_System::save_Student(System & s) {
	s.m_Rooms = this->m_Rooms;
}