#include <iostream>
#include <Windows.h>
#include <string>

//����ָ��ֲ�������ָ�룬��������ʱ���Է��س��������൱���á�
int *text()
{
	int a[] = {1, 2, 3, 4};
	return a;
}

char *test2()
{
	char c[] = "hello world";
	return c;
}

int main(int argc, char **argv)
{
	std::string tmpbuf;
	//WinExec("\"D:\\VMware12\\vmrun.exe\" list", );
	int *a = text();
	char *c = test2();
	std::cout << *c;
	std::cout << *(c + 1) << std::endl;
	std::cout << *(c + 1) << std::endl;
	system("pause");
	return 0;
}