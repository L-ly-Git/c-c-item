#include "room.h"


Room::Room(int id, int capicity) {
	this->m_id = id;
	this->m_capicity = capicity;
	this->m_size.resize(7, 0); //初始化每天为0

	//预约情况需要从预约记录中加载
	this->m_Res.clear(); //先初始化未空

}