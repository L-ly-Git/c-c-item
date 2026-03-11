
#include "contact.h"

//函数声明
//1.初始化
//读取文件
void InitFromFile(LinkNode* qhead) {
	// 前置校验：头节点不能为空
	if (qhead == NULL) {
		printf("链表未初始化，无法读取文件\n");
		return;
	}

	FILE* pf = fopen("contact.txt", "r");
	if (pf == NULL) {
		printf("文件读取失败:%s\n", strerror(errno));
		return;
	}
	LinkNode* qcurrent = qhead;
	//读取文件，直到读取到文件末尾的EOF
	LinkNode* newnode = (LinkNode*)malloc(sizeof(LinkNode));
	if (newnode == NULL) {
		printf("申请空间失败\n");
		return;
	}
	newnode->next = NULL;
	while (fscanf(pf, "%s\t%s\t%s", newnode->data.name, newnode->data.sex, newnode->data.tele) != EOF) {
		qcurrent->next = newnode;
		qcurrent = qcurrent->next;
		newnode = (LinkNode*)malloc(sizeof(LinkNode));
		if (newnode == NULL) {
			printf("申请空间失败\n");
			return;
		}
		newnode->next = NULL;

	}

	//循环结束记得释放空间
	free(newnode);
	newnode = NULL;
	if (feof(pf)) {
		printf("文件正常读取\n");
	}
	else if (ferror(pf)) {
		printf("文件读取错误\n");
		fclose(pf);
		pf = NULL;
		return;
	}

	fclose(pf);
	pf = NULL;
}

LinkNode* InitLinkList() {
	LinkNode* qhead = (LinkNode*)malloc(sizeof(LinkNode));
	if (qhead == NULL) {
		printf("InitLinkList失败\n");
		return NULL;
	}
	strcpy(qhead->data.name, "NULL");
	strcpy(qhead->data.sex, "NULL");
	strcpy(qhead->data.tele, "NULL");

	qhead->next = NULL;

	//读取文件数据
	InitFromFile(qhead);

	printf("链表成功初始化\n");
	return qhead;
}


//2.增加数据
void AddLinkList(LinkNode* qhead) {
	//找到链表末尾
	LinkNode* qcurrent = qhead;
	while (qcurrent->next != NULL) {
		qcurrent = qcurrent->next;
	}

	int num;
	printf("输入要添加的数据个数:");
	scanf("%d", &num);
	while (num > 0) {

		LinkNode* newnode = (LinkNode*)malloc(sizeof(LinkNode));
		if (newnode != NULL) {
			printf("输入要添加的数据:姓名，性别，电话号码:");
			scanf("%s %s %s", newnode->data.name,newnode->data.sex,newnode->data.tele);
			newnode->next = NULL;
			qcurrent->next = newnode;
			qcurrent = newnode;
		}
		num--;
	}
}
//3.插入数据
void InsertLinkList(LinkNode* qhead) {
	LinkNode* qcurrent = qhead->next;
	LinkNode* qPrev = qhead;
	if (qcurrent == NULL) {
		printf("链表为空\n");
		return;
	}
	else {
		char name[MAX_LEN];
		printf("输入要插入的旧数据:插入人的姓名");
		scanf("%s", name);
		while (qcurrent != NULL) {
			if (!(strcmp(qcurrent->data.name,name))) {
				LinkNode* newnode = (LinkNode*)malloc(sizeof(LinkNode));
				if (newnode == NULL) {
					printf("创建新节点失败\n");
					return;
				}
				printf("输入要添加的数据:姓名，性别，电话号码:");
				scanf("%s %s %s", newnode->data.name, newnode->data.sex, newnode->data.tele);
				newnode->next = qcurrent;
				qPrev->next = newnode;
				break;
			}
			qPrev = qPrev->next;
			qcurrent = qcurrent->next;
		}
		if (qcurrent == NULL) {
			printf("未找到目标数据\n");
		}
	}
}
//4.删除数据
void DelLinkList(LinkNode* qhead) {
	LinkNode* qcurrent = qhead->next;
	LinkNode* qPrev = qhead;

	if (qcurrent == NULL) {
		printf("链表为空\n");
		return;
	}

	char name[MAX_LEN];
	printf("输入要删除的人名:");
	scanf("%s", name);

	int find_flag = 0;
	while (qcurrent != NULL) {
		if (strstr(qcurrent->data.name,name)) {
			find_flag = 1;
			int choice = 0;
			printf("是否删除数据:%s %s %s,是输入1,否输入0:", qcurrent->data.name, qcurrent->data.sex, qcurrent->data.tele);
			scanf("%d", &choice);
			if (choice) {
				qPrev->next = qcurrent->next;
				LinkNode* node = qcurrent->next;
				free(qcurrent);
				qcurrent = node;
			}
		}
		qcurrent = qcurrent->next;
		qPrev = qPrev->next;
	}
	if (!find_flag) {
		printf("未找到要删除的数据\n");
	}

}

//5.清空
void ClearLinkList(LinkNode* qhead) {
	LinkNode* qcurrent = qhead->next;
	while (qcurrent != NULL) {
		LinkNode* node = qcurrent->next;

		free(qcurrent);
		qcurrent = node;
	}
	qhead->next = NULL;
	printf("链表已清空\n");
}
//6.销毁
void DestroyLinkList(LinkNode* qhead) {
	int choice = 0;
	printf("是否保存数据:（是1否0）");
	scanf("%d", &choice);
	if (choice) {
		SaveToFile(qhead);
	}
	LinkNode* qcurrent = qhead;
	while (qcurrent != NULL) {
		LinkNode* node = qcurrent->next;
		free(qcurrent);
		qcurrent = node;
	}
	printf("链表已经销毁\n");
}

//7.便利输出
void OutputLinkList(LinkNode* qhead) {
	LinkNode* qcurrent = qhead->next;
	if (qcurrent == NULL) {
		printf("链表为空\n");
		return;
	}
	printf("姓名\t性别\t电话号码\n");
	while (qcurrent != NULL) {
		printf("%s\t%s\t%s\n", qcurrent->data.name,qcurrent->data.sex,qcurrent->data.tele);
		qcurrent = qcurrent->next;
	}
	printf("所有数据已经输出\n");

}

//8.查找
void SearchLinkList(LinkNode* qhead) {
	LinkNode* qcurrent = qhead->next;

	if (qcurrent == NULL) {
		printf("链表为空\n");
		return;
	}

	char name[MAX_LEN];
	printf("输入要查找的人名:");
	scanf("%s", name);

	int find_flag = 0;
	
	while (qcurrent != NULL) {
		if (strstr(qcurrent->data.name, name)) {
			if (!find_flag) {
				printf("姓名\t性别\t电话号码\n");
			}
			find_flag = 1;
			int choice = 0;
			printf("%s\t%s\t%s\n", qcurrent->data.name, qcurrent->data.sex, qcurrent->data.tele);

		}
		qcurrent = qcurrent->next;
	}
	if (!find_flag) {
		printf("未找到要删除的数据\n");
	}

}


//9.写入文件
void SaveToFile(LinkNode* qhead) {
	LinkNode* qcurrent = qhead->next;
	if (qcurrent == NULL) {
		printf("链表为空，无法写入");
		return;
	}
	//打开文件
	FILE* pf = fopen("contact.txt", "w");
	if (pf == NULL) {
		printf("文件写入失败:%s", strerror(errno));
		return;
	}

	while (qcurrent != NULL) {
		fprintf(pf, "%s\t%s\t%s\n", qcurrent->data.name, qcurrent->data.sex, qcurrent->data.tele);
		qcurrent = qcurrent->next;
	}
	printf("文件成功保存\n");

	//关闭文件
	fclose(pf);
	pf = NULL;
}

//清空输出
void Clear() {
	int choice = 0;
	printf("是否清空所有输出:（是:1.否：0）");
	while (1) {
		scanf("%d", &choice);
		if (choice == 1) {
			system(CLEAR_CMD); // 执行系统清屏命令
			break;
		}
		else if (choice == 0) {
			break;
		}
		else {
			printf("请重新输入0（否）或1（是）:");
		}
	}

}