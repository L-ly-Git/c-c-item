#pragma once
#include "head.h"
#include "participant.h"


//系统管理类


class System {
public:
	vector<Participant> pars; //参赛选手数组

public:
	
	System();   //构造函数,初始化类

	void menu();


	void init(); //重新初始化

	int get_LogNum(); //获取总记录次数

	void out_csv(); //输出往届比赛记录

	void cls_csv(); //清空往届记录

	void save();  //记录 

	void show(); //输出选手成绩

	void contest_single(vector<Participant>& pars_temp); //单次比赛流程 ，评分，淘汰，展示晋级选手

	void contest1(); //第一轮分组淘汰赛

	void contest2(); //决赛

	void contest_All(); //整体比赛流程
	
};

//评分系统
class Get_Point {

public:
	void operator()(Participant& par) {
		deque<int> points;
		//随机生成10个分数
		for (int i = 0; i < 10; i++) {
			int point = rand() % 41 + 60;
			points.push_back(point);
		}
		//排序
		sort(points.begin(), points.end());

		//去除最高最低分
		points.pop_back();
		points.pop_front();

		double sum = accumulate(points.begin(), points.end(), 0);// 计算总分
		par.m_point = sum / points.size(); //记录平均分
	}

};


