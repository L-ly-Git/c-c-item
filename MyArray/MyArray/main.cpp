#include "MyArray.hpp"

void test() {
	MyArray<int> arr1(5);
	arr1.Add();
	arr1.show_info();
	cout << arr1[3] << endl;
	MyArray<int> arr2(arr1);

	arr2.show_info();

	MyArray<int> arr3(6);
	arr3 = arr1;
	arr3.show_info();
}

int main() {
	test();

	system("pause");

	return 0;
}