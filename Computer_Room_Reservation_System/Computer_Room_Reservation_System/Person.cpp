#include "Person.h"

//学生
//构造函数
Student::Student(string id, string name, string password) {
	this->m_Id = id;
	this->m_Name = name;
	this->m_Password = password;
}

//重载相等函数
bool Student::operator== (const Student& s) {
	return (this->m_Id == s.m_Id && this->m_Name == s.m_Name && this->m_Password == s.m_Password);
}


//教师
//构造函数
Teacher::Teacher(string id, string name, string password) {
	this->m_Id = id;
	this->m_Name = name;
	this->m_Password = password;
}

//重载相等函数
bool Teacher::operator== (const Teacher& t) {
	return (this->m_Id == t.m_Id && this->m_Name == t.m_Name && this->m_Password == t.m_Password);
}



//管理员
//构造
Admin::Admin(string name, string password) {
	this->m_Name = name;
	this->m_Password = password;
}

//重载相等函数
bool Admin::operator== (const Admin& a) {
	return (this->m_Name == a.m_Name && this->m_Password == a.m_Password);
}

