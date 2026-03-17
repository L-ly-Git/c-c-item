#include "EMS.h"

CommonWorker::CommonWorker(int id, string name, int deptid) {
	m_id = id;
	m_name = name;
	m_Deptid = deptid;
}

void CommonWorker::showinfo() {
	cout << "员工id:" << m_id << "\t";
	cout << "职工姓名:" << m_name << "\t";
	cout << "部门编号:" << m_Deptid << "\t";
	cout << "员工岗位:" << this->getDepName()<< "\t";
	cout << "职责:完成上级交代的任务" << endl;
}

string CommonWorker::getDepName(){
	return "普通职工";
}

Manager::Manager(int id, string name, int deptid) {
	m_id = id;
	m_name = name;
	m_Deptid = deptid;
}

void Manager::showinfo() {
	cout << "员工id:" << m_id << "\t";
	cout << "职工姓名:" << m_name << "\t";
	cout << "部门编号:" << m_Deptid << "\t";
	cout << "员工岗位:" << this->getDepName() << "\t";
	cout << "职责:完成老板交代的任务或者下发任务给普通员工" << endl;
}

string Manager::getDepName() {
	return "经理";
}

Boss::Boss(int id, string name, int deptid) {
	m_id = id;
	m_name = name;
	m_Deptid = deptid;
}

void Boss::showinfo() {
	cout << "员工id:" << m_id << "\t";
	cout << "职工姓名:" << m_name << "\t";
	cout << "部门编号:" << m_Deptid << "\t";
	cout << "员工岗位:" << this->getDepName() << "\t";
	cout << "职责:下发任务给经理或普通员工" << endl;
}

string Boss::getDepName() {
	return "老板";
}