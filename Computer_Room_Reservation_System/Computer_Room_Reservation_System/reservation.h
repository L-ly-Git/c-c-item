#include "head.h"


//单次预约类
class Reservation {
public:
	string roomname; //预约的机房
	string m_Name; //预约人姓名
	string m_Id; //预约人id 
	string m_Date; //预约日期
	string m_Situation;//预约状态 --- 审核中，取消预约 ， 审核通过，审核未通过

public:
	Reservation(string roommane,string name, string id, string date, string situation) {
		this->roomname = roommane;
		this->m_Name = name;
		this->m_Id = id;
		this->m_Date = date;
		this->m_Situation = situation;
	}
};