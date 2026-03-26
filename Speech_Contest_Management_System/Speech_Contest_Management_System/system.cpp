#include "System.h"

System::System() {
	
	string ids[] = { "01","02","03","04","05","06","07","08","09","10","11","12" };
	//初始还12为选手
	for (int i = 0; i < 12; i++) {
		string id = "100" + ids[i];
		Participant par(id);

		pars.push_back(par);
	}

}   //初始化类

void System::menu() {
	cout << "==========欢迎使用演讲比赛管理系统============" << endl;
	cout << "==========  1.开始第一次完整比赛  ============" << endl;
	cout << "==========  2.再次开始完整比赛	  ============" << endl;
	cout << "==========  3.输出往届记录	  ============" << endl;
	cout << "==========  4.清空往届记录	  ============" << endl;
	cout << "==========  0.退出系统		  ============" << endl;
	cout << "请输入你的选择:";

}

void System::init() {
	string ids[] = { "01","02","03","04","05","06","07","08","09","10","11","12" };
	
	pars.clear();//清空原数组

	//初始还12为选手
	for (int i = 0; i < 12; i++) {
		string id = "100" + ids[i];
		Participant par(id);

		pars.push_back(par);
	}
} //重新初始化

void System::contest_single(vector<Participant>& pars_temp) {
	//评分
	for_each(pars_temp.begin(), pars_temp.end(), Get_Point()); 

	//排序，淘汰后面3人
	sort(pars_temp.begin(), pars_temp.end(), Sort_Participant());

	//输出前三名，删除后三人
	for (int i = 0; i < 6; i++) {
		if (i < 3) {
			pars_temp[i].show_info();
		}
		else {
			pars_temp[i].show_info();
		}
	}

	//淘汰后面三人
	pars_temp.erase(pars_temp.begin() + 3, pars_temp.end());

}
//单次比赛流程 ，评分，淘汰，展示晋级选手

void System::show() {
	for (vector<Participant>::iterator it = this->pars.begin(); it != this->pars.end(); it++) {
		cout << it->m_Id << " ";
	}
}

void System::contest1() {
	//随机打乱pars顺序，进行分组
	cout << "====================开始抽签决定演讲顺序以及分组===================" << endl;
	random_shuffle(pars.begin(), pars.end()); 
	vector<Participant> pars_temp1(6); //分组1
	vector<Participant> pars_temp2(6); //分组2
	cout << "演讲顺序为:";
	show();
	cout << endl;

	copy(pars.begin(), pars.begin() + 6, pars_temp1.begin()); // 降乱序后前6名给到分组1
	copy(pars.begin() + 6, pars.end(), pars_temp2.begin());  //乱序后后6名，给到分组2

	system("pause");

	//进行比赛,得到两组淘汰后的结果
	cout << "晋级赛第一轮淘汰赛名次如下" << endl;
	this->contest_single(pars_temp1);
	cout << "晋级赛第二轮淘汰赛名次如下" << endl;
	this->contest_single(pars_temp2); 

	system("pause");
	//将两个结果合并给到pars;
	//先重新定义大小
	pars.resize(6);
	pars = pars_temp1;
	//copy(pars_temp2.begin(), pars_temp2.end(), pars.begin() + 3);
	for (auto& par : pars_temp2) {
		pars.push_back(par);
	}
	cout << "晋级选手名单如下:";
	show();
	cout << endl;

	system("pause");

} //第一轮分组淘汰赛

void System::contest2() {
	//进行决赛
	cout << "决赛";

	cout << "====================开始抽签决定演讲顺序===================" << endl;
	random_shuffle(pars.begin(), pars.end());
	cout << "演讲顺序为:";
	show();
	cout << endl;
	system("pause");

	cout << "决赛名次如下" << endl;
	this->contest_single(this->pars);

	system("pause");

	cout << "最终晋级选手:";
	show();

} //决赛


void System::contest_All() {
	
	//第一轮比赛，晋级赛
	this->contest1();
	cout << endl;
	//决赛
	this->contest2();

	cout << "比赛完毕" << endl;
	this->save();

}//整体比赛流程



int System::get_LogNum() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);


	string id;
	int point;
	int num = 0;
	while (ifs >> id && ifs >> point) {
		num++;
	}

	return num/3;  //每3行记录对应一届
}

void System::out_csv() {
	//创建对象
	ifstream ifs;
	//打开文件
	ifs.open(FILENAME, ios::in);
	//1.文件未打开
	if (!ifs.is_open()) {
		cout << "文件未创建，打开失败" << endl;
		//关闭文件
		ifs.close();
		return;
	}

	//获取当前文件内数据个数
	int num = this->get_LogNum();

	//2.num==0,说明文件打开成功，但是没有存储数据
	if (num == 0) {
		cout << "文件为空，没有往届记录" << endl;
		//关闭文件
		ifs.close();

		return;
	}

	//3.num>0,文件不为空
	cout << "往届记录如下:" << endl;
	//开始读取数据

	string id;
	int point;

	for (int i = 0; i < num; i++) {
		cout << "=================================================" << endl;
		cout << "第" << i+1 << "届" << endl;
		for (int j = 0; j < 3; j++) {
			ifs >> id;
			ifs >> point;
			cout << "第" << j + 1 << "名:" << "编号:" << id << " 得分" << point << endl;
		}
	}

	//关闭文件
	ifs.close();

}

void System::save() {
	//创建流对象
	ofstream ofs;
	//打开文件
	ofs.open(FILENAME, ios::app);

	//写入数据
	for (int i = 0; i < 3; i++) {
		ofs << this->pars[i].m_Id << " "
			<< this->pars[i].m_point << endl;
	}


	//关闭文件
	ofs.close();
}

void System::cls_csv() {
	//创建流对象
	ofstream ofs;
	//打开文件
	ofs.open(FILENAME, ios::out);

	//写入数据
	ofs << "";

	cout << "已经清空文件" << endl;
	//关闭文件
	ofs.close();
}