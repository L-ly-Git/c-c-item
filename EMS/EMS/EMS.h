#pragma once

#include <iostream>
#include <string>
#include <fstream>
#define FILENAME "Worker.txt"

using namespace std;
class Abstractworker;
class CommonWorker;
class Manager;
class Boss;


//构造管理类
class WorkerManage {
public:

	//构造函数
	WorkerManage();
	
	//文件读取数据
	int get_EmpNum();

	//菜单
	void Menu();

	//退出函数
	void exit_sys();

	//添加职工
	void AddWorker();

	//输出全部职工
	void OutWorker();

	//删除职工
	void DelWorker();

	//修改职工
	void ChangeWorker();

	//查找员工
	void FindWorker();

	//按照职工编号
	void SortWorker();

	//清空职工
	void ClearWorker();

	//保存文件
	void save();

	//析构函数
	~WorkerManage();

	
	//记录职工人数
	int m_EmpNum;

	//职工数组指针
	Abstractworker** m_EmpArray; //接收new Abstractworker*[];

	//文件是否为空
	bool m_FileIsEmpty;


};


//构造抽象员工类
class Abstractworker {
public:
	//显示员工信息
	virtual void showinfo() = 0;
	
	//获取岗位名称
	virtual string getDepName() = 0;

	int m_id;
	string m_name;
	int m_Deptid;
};


//普通职工
class CommonWorker :public Abstractworker {
public:
	CommonWorker(int id, string name, int deptid);

	virtual void showinfo();

	virtual string getDepName();

};

//管理
class Manager:public Abstractworker {
public:
	Manager(int id, string name, int deptid);

	virtual void showinfo();

	virtual string getDepName();

};

//老板
class Boss :public Abstractworker {
public:
	Boss(int id, string name, int deptid);

	virtual void showinfo();

	virtual string getDepName();

};