#include "head.h"
#include "room.h"
#include "Person.h"

class System {
public:

	//构造函数
	System();

	//菜单
	void menu();
	
	//从文件中获取数据
	vector<string> info_from_file(string filename);

	vector<string> split(const string& str, char delimiter); //分割获得整行数据

	//输出完整预约信息
	void reservation_info();

	//保存，自动保存
	 void save();

	

public:

	vector<Room> m_Rooms;
	vector<Student> m_Stus;
	vector<Teacher> m_Teachers;
	vector<Admin> m_Admins; 
};

//定义三个子类
//学生系统
class Stu_System :public System {
public:
	//构造函数,继承主系统的数据和函数
	Stu_System(const System& s);

	//登录
	bool sys_in_Stu(const Student& stu);

	//菜单
	void student_menu();

	//查看所有预约情况 

	//查看预约信息
	void show_log_info(const Student& stu);

	//进行预约
	void reservate(const Student& stu);

	//取消预约
	void change_reservation(const Student& stu);

	void sys_stu(); //学生系统整体操作

	//保存回主系统的数据
	void save_Student(System& s);

};

//教师系统
class Teacher_System :public System {
public:
	//构造函数，继承主系统数据
	Teacher_System(const System& s);
	
	//登录
	bool sys_in_Teacher();

	//菜单
	void teacher_menu();

	//查看所有预约情况 

	//进行审核
	void check();

	void sys_teacher(); //教师系统整体操作

	//保存数据会主系统
	void save_Teacher(System& s); 
};


//管理员系统
class Admin_System :public System {
public:
	//构造函数，继承主系统
	Admin_System(const System& s);
	
	//登录
	bool sys_in_Admin();

	//菜单
	void Admin_menu();

	//查看学生类
	void show_Student();

	//查看教师类
	void show_Teacher();

	//添加人员
	void Add_Person();

	//删除人员
	void Del_Person();

	//查看预约信息和当前机房状态
	void show_log();

	//情况当前预约情况
	void clear_log();

	void sys_admin(); //管理元系统整体操作

	//保存数据会主系统
	void save_Admin(System& s);
};
