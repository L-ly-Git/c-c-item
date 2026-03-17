#include "EMS.h"



WorkerManage::~WorkerManage(){
	if (this->m_EmpArray != NULL) {
		delete this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}

void WorkerManage::Menu() {
	cout << "********************************************" << endl;
	cout << "************** 0.退出管理系统 **************" << endl;
	cout << "************** 1.增加职工信息 **************" << endl;
	cout << "************** 2.显示职工信息 **************" << endl;
	cout << "************** 3.删除职工信息 **************" << endl;
	cout << "************** 4.修改职工信息 **************" << endl;
	cout << "************** 5.查找职工信息 **************" << endl;
	cout << "************** 6.按照编号排序 **************" << endl;
	cout << "************** 7.清空职工信息 **************" << endl;
	cout << "************** 8.保存职工信息 **************" << endl;
	cout << "********************************************" << endl;

}


void WorkerManage::exit_sys() {
	cout << "退出系统" << endl;
	exit(0);
}


WorkerManage::WorkerManage() {
	//创建对象
	ifstream ifs;
	//打开文件
	ifs.open(FILENAME, ios::in);
	//1.文件未打开
	if (!ifs.is_open()) {
		cout << "文件未创建，打开失败" << endl;
		this->m_FileIsEmpty = true;
		this->m_EmpNum = 0; //初始化员工个数为0
		this->m_EmpArray = NULL; //初始化为空指针
		
		//关闭文件
		ifs.close();

		return;
	}

	//获取当前文件内数据个数
	int num = this->get_EmpNum();
	
	//2.num==0,说明文件打开成功，但是没有存储数据
	if (num == 0) {
		cout << "文件为空" << endl;
		this->m_FileIsEmpty = true;
		this->m_EmpNum = 0; //初始化员工个数为0
		this->m_EmpArray = NULL; //初始化为空指针

		//关闭文件
		ifs.close();

		return;
	}
	
	//3.num>0,文件不为空
	cout << "开始从文件读取数据" << endl;
	this->m_EmpNum = num;
	this->m_EmpArray = new Abstractworker * [num]; 
	this->m_FileIsEmpty = false;
	//开始读取数据
	int id;
	string name;
	int dpsid;

	for (int i = 0; i < this->m_EmpNum; i++) {
		Abstractworker* worker = NULL;
		ifs >> id;
		ifs >> name;
		ifs >> dpsid;

		switch (dpsid) {
		case 1:
			worker = new Boss(id, name, dpsid);
			break;
		case 2:
			worker = new Manager(id, name, dpsid);
			break;
		case 3:
			worker = new CommonWorker(id, name, dpsid);
			break;
		default:
			break;
		}

		this->m_EmpArray[i] = worker;
	}

	cout << "已经成功在文件中读取数据" << endl;
	//关闭文件
	ifs.close();



}

int WorkerManage::get_EmpNum() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int Dpsid;
	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> Dpsid) {
		num++;
	}

	return num;
}


void WorkerManage::AddWorker() {
	int num;
	cout << "输入你要添加的职工个数" << endl;
	cin >> num;

	if (num > 0) {
		int newsize = this->m_EmpNum + num;
		Abstractworker** newArray = new Abstractworker * [newsize]; //创建新的数组指针对象用于存储新数据

		if (this->m_EmpArray != NULL) { //将原数据赋值到新指针中
			for (int i = 0; i < this->m_EmpNum; i++) {
				newArray[i] = this->m_EmpArray[i];
			}
		}

		for (int j = 0; j < num; j++) {
			int id;
			string name;
			int depname;
			
			cout << "请输入员工编号:";
			cin >> id;

			cout << "请输入员工姓名";
			cin >> name;


			cout << "请输入员工岗位"<<endl;
			cout << "1.老板" << endl;
			cout << "2.经理" << endl;
			cout << "3.普通员工" << endl;
			cin >> depname;

			Abstractworker* worker = NULL;
			switch (depname)
			{
			case 1:
				worker = new Boss(id, name, depname);
				break;
			case 2:
				worker = new Manager(id, name, depname);
				break;
			case 3:
				worker = new CommonWorker(id, name, depname);
				break;
			default:
				break;
			}

			newArray[this->m_EmpNum + j] = worker;
		}

		if (this->m_EmpArray != NULL) {
			delete this->m_EmpArray;
		}

		this->m_EmpArray = newArray;
		this->m_EmpNum = newsize;
		this->m_FileIsEmpty = false;
	}
	else {
		cout << "输入数据有误" << endl;
	}

	cout << "成功添加" << endl;
}

void WorkerManage::OutWorker() {
	cout << "开始输出" << endl;

	if (this->m_EmpNum == 0) {
		cout << "当前职工个数为0" << endl;
		return;
	}

	cout << "总职工个数:" << this->m_EmpNum << endl;
	for (int i = 0; i < this->m_EmpNum; i++) {
		//利用多态调用程序接口
		this->m_EmpArray[i]->showinfo();
	}

}

void WorkerManage::DelWorker() {
	//先判断是否存在职工
	if (this->m_EmpNum == 0) {
		cout << "当前职工已经为0" << endl;
		return;
	}

	//创建新数组，以存储对象
	Abstractworker** newArray = new Abstractworker * [this->m_EmpNum];
	int num = 0; 

	string name;
	cout << "输入你要删除的职工姓名" << endl;
	cin >> name;
	//遍历寻找是否需要删除
	for (int i = 0; i < this->m_EmpNum; i++) {
		//不是目标对象，复制到newArray中
		if (name != this->m_EmpArray[i]->m_name) {
			newArray[num++] = this->m_EmpArray[i];
		}
		//是目标对象，不需要存储，不需要其他操作
	}
	//newArray中的数目小于原来的数目，说明实现了删除
	if (num < this->m_EmpNum) {
		cout << "成功删除" << endl;
		this->m_EmpNum = num;
		//先释放原指针
		delete this->m_EmpArray;
		//指向新的地址
		if (this->m_EmpNum == 0) {
			this->m_EmpArray = NULL;
			delete newArray;
			newArray = NULL;
		}
		else 
			this->m_EmpArray = newArray;
	}
	else {
		cout << "未找到目标" << endl;
	}



}

void WorkerManage::ChangeWorker() {
	if (this->m_FileIsEmpty) {
		cout << "当前职工已经为0" << endl;
		return;
	}
	string name;
	cout << "输入你要修改的职工" << endl;
	cin >> name;

	int is_change = 0;
	for (int i = 0; i < this->m_EmpNum; i++) {
		if (name == this->m_EmpArray[i]->m_name) {
			is_change = 1;
			int id;
			int dpsid;
			this->m_EmpArray[i]->showinfo();
			cout << "请输入新的员工编号" << endl;
			cin >> id;

			cout << "请输入新的员工岗位" << endl;
			cout << "1.老板" << endl;
			cout << "2.经理" << endl;
			cout << "3.普通员工" << endl;
			cin >> dpsid;
			Abstractworker* worker = NULL;

			switch (dpsid) {
			case 1:
				worker = new Boss(id, name, dpsid);
				break;
			case 2:
				worker = new Manager(id, name, dpsid);
				break;
			case 3:
				worker = new CommonWorker(id, name, dpsid);
				break;
			default:
				break;
			}
			this->m_EmpArray[i] = worker;

		}
	}
	if (is_change) {
		cout << "已经完成修改" << endl;
	}
	else {
		cout << "未找到要修改的职工" << endl;
	}
}

void WorkerManage::FindWorker() {
	if (this->m_FileIsEmpty) {
		cout << "当前职工已经为0" << endl;
		return;
	}
	string name;
	cout << "输入你要查找的职工" << endl;
	cin >> name;

	int is_find = 0;
	for (int i = 0; i < this->m_EmpNum; i++) {
		if (name == this->m_EmpArray[i]->m_name) {
			is_find = 1;
			this->m_EmpArray[i]->showinfo();
		}
	}
	if(!is_find) {
		cout << "未找到要查找的职工" << endl;
	}

}

void WorkerManage::SortWorker() {
	if (this->m_FileIsEmpty) {
		cout << "当前总员工数为0，无法排序" << endl;
		return;
	}

	int num = this->m_EmpNum;
	int cnt = 0;
	while (num > 1) {
		for (int i = 0; i < num-1; i++) {
			if (this->m_EmpArray[i]->m_id > this->m_EmpArray[i + 1]->m_id) {
				Abstractworker* worker = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
				this->m_EmpArray[i + 1] = worker;
				cnt++;
			}
		}
		if (cnt == 0) {
			break;
		}
		cnt = 0;
		num--;
	}

	cout << "已经完成排序" << endl;

}

void WorkerManage::ClearWorker() {
	if (this->m_FileIsEmpty) {
		cout << "已经为空，不需要清空" << endl;
	}

	//一次释放数组中指针
	for (int i = 0; i < this->m_EmpNum; i++) {
		delete this->m_EmpArray[i];
		this->m_EmpArray[i] = NULL;
	}
	//释放数组指针
	delete this->m_EmpArray;
	this->m_EmpArray = NULL;
	//初始化
	this->m_EmpNum = 0;
	this->m_FileIsEmpty = true;
	cout << "已经完成清空" << endl;
}

void WorkerManage::save() {
	//创建流对象
	ofstream ofs;
	//打开文件
	ofs.open(FILENAME, ios::out);

	//写入数据
	for (int i = 0; i < this->m_EmpNum; i++) {
		ofs << this->m_EmpArray[i]->m_id << " "
			<< this->m_EmpArray[i]->m_name << " "
			<< this->m_EmpArray[i]->m_Deptid << endl;
	}

	//关闭文件
	ofs.close();
}