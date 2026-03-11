#pragma once


#ifdef cplusplus
extern "C" {
#endif
	#define _CRT_SECURE_NO_WARNINGS
	#define MAX_LEN 20

	#include <stdio.h>

	#include <string.h>
	#include <errno.h>

	#include <stdlib.h> // system() 所需
	#ifdef _WIN32       // Windows 系统标识
	#define CLEAR_CMD "cls"
	#else               // Linux/macOS 系统标识	
	#define CLEAR_CMD "clear"
	#endif

	//定义数据类型
	typedef struct _Data {
		char name[MAX_LEN];
		char sex[MAX_LEN];
		char tele[MAX_LEN];
	}Data;

	typedef struct LinkNode {
		Data data;
		struct LinkNode* next;
	}LinkNode;

	//函数声明
	//1.初始化
	LinkNode* InitLinkList();
	void InitFromFile(LinkNode* qhead);
	//2.增加数据
	void AddLinkList(LinkNode* qhead);
	//3.插入数据
	void InsertLinkList(LinkNode* qhead);
	//4.删除数据
	void DelLinkList(LinkNode* qhead);
	//5.清空
	void ClearLinkList(LinkNode* qhead);
	//6.销毁
	void DestroyLinkList(LinkNode* qhead);
	//7.遍历输出
	void OutputLinkList(LinkNode* qhead);
	//8.查找
	void SearchLinkList(LinkNode* qhead);
	//9.保存数据写入文件
	void SaveToFile(LinkNode* qhead);
	//清空输出
	void Clear();



#ifdef cplusplus
}
#endif // cplusplus


