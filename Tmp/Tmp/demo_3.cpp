#include <iostream>
#include <Windows.h>


int main3(int argc, char **argv)
{
	DWORD id = WTSGetActiveConsoleSessionId();
	std::cout << id << std::endl;
	system("pause");
	return 0;
}