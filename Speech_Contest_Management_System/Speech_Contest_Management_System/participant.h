#include "head.h"

class Participant {
public:
	string m_Id; //编号
	double m_point; //平均分

public:

	//无参构造（必须加！） //为了之后重定义大小
	Participant();

	//初始化
	Participant(string id);
	//信息展示
	void show_info();
};

//比较方式
class Sort_Participant {
public:
	bool operator()(const Participant& p1, const Participant& p2) {
		//按照得分的降序排列
		return p1.m_point > p2.m_point;
	}
};