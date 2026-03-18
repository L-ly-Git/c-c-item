#pragma once

#include <iostream>
#include <string>

using namespace std;

template <typename T>
class MyArray {
private:
	T* m_Array; //指向堆区开辟的数组
	int m_Num; //数组元素个数
	int m_Max_Num; //数组容量

public:
	//构造函数，可提供容量
	MyArray(int max_num) {
		cout << "有参构造调用" << endl;
		this->m_Max_Num = max_num;
		this->m_Num = 0;
		this->m_Array = new T[max_num];
	}
	
	//拷贝构造函数
	MyArray(MyArray& arr) {
		cout << "拷贝构造调用" << endl;
		this->m_Max_Num = arr.m_Max_Num;
		this->m_Num = arr.m_Num;

		//深复制
		this->m_Array = new T[this->m_Max_Num];
		for (int i = 0; i < this->m_Num; i++) {
			this->m_Array[i] = arr.m_Array[i];
		}

	}

	//赋值"="重载，防止浅拷贝
	void operator= (const MyArray& arr) {
		cout << "赋值操作" << endl;
		if (this->m_Array != NULL) {
			delete this->m_Array;
		}

		//深复制
		this->m_Max_Num = arr.m_Max_Num;
		this->m_Num = arr.m_Num;
		this->m_Array = new T[arr.m_Max_Num];
		for (int i = 0; i < arr.m_Num; i++) {
			this->m_Array[i] = arr.m_Array[i];
		}

	}

	//[]重载，实现按下表访问
	T operator[] (int i) {
		return this->m_Array[i];
	}

	void show_info() {
		cout << "容量:" << this->m_Max_Num << endl;
		cout << "个数:" << this->m_Num << endl;
		for (int i = 0; i < this->m_Num; i++) {
			cout << this->m_Array[i] << " ";
		}
		cout << endl;
	}

	//增加数字
	void Add() {
		int add_num = 0;
		cout << "请输入要添加的个数" << endl;
		cin >> add_num;
		if (add_num + this->m_Num > this->m_Max_Num) {
			cout << "添加后数组大小将要超过其容量，是否更改容量未添加后总大小" << endl;
			cout << "请输入1(是),0(否):";
			int choice = 1;
			cin >> choice;
			if (!choice) {
				cout << "取消添加" << endl;
				return;
			}
			else {
				this->m_Max_Num = this->m_Num + add_num;
			}
		}
		if (this->m_Num == 0) {
			this->m_Array = new T[this->m_Max_Num];
		}
		for (int i = 0; i < add_num; i++) {
			cout << "请输入要添加的数据:" ;
			T add_T;
			cin >> add_T;
			this->m_Array[this->m_Num + i] = add_T;
		}
		this->m_Num += add_num;
	}

	//析构函数
	~MyArray() {
		cout << "构烯函数调用" << endl;
		if (this->m_Array != NULL) {
			delete this->m_Array;
			this->m_Array = NULL;
		}
	}

};


