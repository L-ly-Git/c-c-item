#include "head.h"


//定义学生类
class Student {
public:
	string m_Id;
	string m_Name;
	string m_Password;

public:
	//构造函数
	Student(string id, string name, string password);
	
	//重载相等函数
	bool operator== (const Student& s);
};

//定义教师类
class Teacher {
public:
	string m_Id;
	string m_Name;
	string m_Password;

public:
	//构造函数
	Teacher(string id,string name,string password);

	//重载相等函数
	bool operator== (const Teacher& t);


};

//定义管理员
class Admin {
public:
	string m_Name;
	string m_Password;
public:
	//构造
	Admin(string name,string password);
	
	//重载相等函数
	bool operator== (const Admin& a);


};