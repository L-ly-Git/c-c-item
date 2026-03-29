#include "system.h"

//记录各个机房容量
const vector<int> capicity_rooms = { 20,30,50 };

System::System() {

	vector<string> datas;
	//初始话机房对象，从文件加载预约信息
	for (int i = 0; i < room_num; i++) {
		Room r(i, capicity_rooms[i]);
		//添加房间预约信息
		datas = this->info_from_file(Log_File);
		for (vector<string>::iterator it = datas.begin(); it != datas.end(); it++) {

			vector<string> res = this->split((*it), ',');
			if (("机房"+to_string(i+1)) == res[0]) {
				//机房名，姓名，学号，预约时间，预约状态
				Reservation re(res[0],res[1], res[2], res[3], res[4]);
				r.m_Res.push_back(re);
				r.m_size[stoi(res[3])-1]++; // 用1，2，3，4，5，6，7代表星期
			} // 如果预约房间相等

		}
		this->m_Rooms.push_back(r); 
		
	}

	
	string id;
	string name;
	string password;

	//初始化学生数组
	datas = this->info_from_file(Student_File);

	for (vector<string>::iterator it = datas.begin(); it != datas.end(); it++) {

		vector<string> res = this->split((*it),',');

		id = res[0];
		name = res[1];
		password = res[2];
		Student s(id, name, password);
		this->m_Stus.push_back(s);
	}

	//初始化教师数组
	datas = this->info_from_file(Teacher_File);
	for (vector<string>::iterator it = datas.begin(); it != datas.end(); it++) {
		vector<string> res = this->split((*it), ',');
		id = res[0];
		name = res[1];
		password = res[2];
		Teacher t(id, name, password);
		this->m_Teachers.push_back(t);
	}

	//初始化管理员数组
	datas = this->info_from_file(Admin_File);
	for (vector<string>::iterator it = datas.begin(); it != datas.end(); it++) {
		vector<string> res = this->split((*it), ',');
		name = res[0];
		password = res[1];
		Admin a(name, password);
		this->m_Admins.push_back(a);
	}

}

void System::menu() {
	cout << "================欢迎使用机房预约系统================" << endl;
	cout << "================1.学生            =================" << endl;
	cout << "================2.老师            =================" << endl;
	cout << "================3.管理员          ================" << endl;
	cout << "================0.退出系统       ================" << endl;
}


vector<string> System::split(const string& str, char delimiter) {
	vector<string> res; //存储分割后字符串
	string temp; //存储临时字符串
	for (char c : str) {
		if (c != delimiter) {
			temp += c;
		}
		else {
			if (!temp.empty()) {
				res.push_back(temp);
				temp.clear();
			}
		}
	}
	res.push_back(temp);

	return res;
}; //分割获得整行数据

vector<string> System::info_from_file(string filename) {
	//创建流
	ifstream ifs;
	//打开文件
	ifs.open(filename, ios::in);
	
	//逐行读取文件
	string data;
	vector<string> datas; //存储获得数据
	//判断是否成功
	if (!ifs.is_open()) {
		cout <<filename <<"文件打开失败" << endl;
		return datas;
	}
	while (ifs >> data) {
		datas.push_back(data);
	}

	ifs.close();
	return datas;
}


void System::reservation_info() {
	int sum = 0;
	for (int i = 0; i < room_num; i++) {
		sum += this->m_Rooms[i].m_Res.size();
	}
	if (sum == 0) {
		cout << "预约情况为空" << endl;
		return;
	}
	for (int i = 0; i < room_num; i++) {
		for (vector<Reservation>::iterator it = this->m_Rooms[i].m_Res.begin(); it != this->m_Rooms[i].m_Res.end(); it++) {
			cout << (*it).roomname << " " << (*it).m_Name << " " << (*it).m_Id << " 星期" << (*it).m_Date << " " << (*it).m_Situation << endl;
		}
	}
}

//保存，自动保存
void System::save() {
	ofstream ofs;

	//保存预约信息
	ofs.open(Log_File, ios::out); 
	for (int i = 0; i < room_num; i++) {
		for (vector<Reservation>::iterator it = this->m_Rooms[i].m_Res.begin(); it != this->m_Rooms[i].m_Res.end(); it++) {
			ofs << (*it).roomname << "," << (*it).m_Name << "," << (*it).m_Id << "," << (*it).m_Date << "," << (*it).m_Situation << endl; //逐行输入
		}
	}
	ofs.close();

	//保存学生信息
	ofs.open(Student_File, ios::out);
	for (vector<Student>::iterator it = this->m_Stus.begin(); it != this->m_Stus.end(); it++) {
		ofs << (*it).m_Id << "," << (*it).m_Name << "," << (*it).m_Password << endl;
	}
	ofs.close();

	//保存教师信息
	ofs.open(Teacher_File, ios::out);
	for (vector<Teacher>::iterator it = this->m_Teachers.begin(); it != this->m_Teachers.end(); it++) {
		ofs << (*it).m_Id << "," << (*it).m_Name << "," << (*it).m_Password << endl;
	}
	ofs.close();

	//保存管理员信息 //似乎不需要？
	ofs.open(Admin_File, ios::out);
	for (vector<Admin>::iterator it = this->m_Admins.begin(); it != this->m_Admins.end(); it++) {
		ofs <<(*it).m_Name << "," << (*it).m_Password << endl;
	}
	ofs.close();
	
}