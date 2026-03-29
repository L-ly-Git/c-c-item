#include "head.h"
#include "reservation.h"

class Room {
public:
	int m_id; //机房id
	int m_capicity; // 容量
	vector<int> m_size;    //一周7天已经预约的人数
	vector<Reservation> m_Res; //机房的预约状态

public:
	//构造机房
	Room(int id, int capicity);

};