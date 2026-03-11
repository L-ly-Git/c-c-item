#include "contact.h"


void test() {
	LinkNode* qhead = InitLinkList();
	int choice = -1;
	while (choice != 0) {
		printf("===========输入选择的功能============\n");
		printf("======0:退出=====1:初始化链表========\n");
		printf("======2:增加=====3:插入数据==========\n");
		printf("======4:删除=====5:清空数据==========\n");
		printf("======6.遍历输出==7:查找数据=========\n");
		printf("======8.保存数据到文件===============\n");
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			qhead = InitLinkList();
			Clear();
			break;
		case 2:
			AddLinkList(qhead);
			Clear();
			break;
		case 3:
			InsertLinkList(qhead);
			Clear();
			break;
		case 4:
			DelLinkList(qhead);
			Clear();
			break;
		case 5:
			ClearLinkList(qhead);
			Clear();
			break;
		case 6:
			OutputLinkList(qhead);
			Clear();
			break;
		case 7:
			SearchLinkList(qhead);
			Clear();
			break;
		case 8:
			SaveToFile(qhead);
			Clear();
			break;
		case 0:
			break;
		default:
			printf("请按照菜单选择功能\n");
			break;
		}
	}
	DestroyLinkList(qhead);

}

int main()
{
	test();
	return 0;
}
