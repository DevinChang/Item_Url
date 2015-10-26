#include <iostream>


union number
{
	int i;
	struct __half
	{
		char first;
		char second;
	}_half;
}num;

struct _student
{
	char a;
	long b;
	float c;
};

int main4(int argc, char ** argv)
{
	_student s;
	std::cout << "sizeof: " << sizeof(s) << std::endl;

	num.i = 0x1234;

	std::cout << num._half.first << " " << num._half.second << std::endl;
	num._half.first = 'a';
	num._half.second = 'b';
	std::cout << num.i << std::endl;

	system("pause");
	return 0;
}