#include "participant.h"

Participant::Participant() {
	m_Id = "";
	m_point = 0;
}

//初始化
Participant::Participant(string id) {
	m_Id = id;
	m_point = 0;
}

//展示信息
void Participant::show_info() {
	cout << "编号:" << m_Id << " 得分:" << m_point << endl;
}