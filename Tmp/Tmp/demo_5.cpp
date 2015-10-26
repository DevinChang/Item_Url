#include <iostream>
#include <Windows.h>


int main5(int argc, char **argv)
{
	WIN32_FIND_DATA fd;
	char tmp_path[260] = {0};
	GetTempPath(260, tmp_path);
	std::cout << tmp_path << std::endl;
	char file_path[260] = {0};
	sprintf(file_path, "%s*.*", tmp_path);
	std::cout << file_path << std::endl;
	//'.'代表本目录，‘..’代表上级目录
	HANDLE hd = ::FindFirstFile(file_path, &fd);
	
	if (hd == INVALID_HANDLE_VALUE)
	{
		std::cout << "can not find!" << std::endl;
		system("pause");
		return 0;
	}
	std::cout << fd.cFileName << std::endl;
	FindNextFile(hd, &fd);
	std::cout << fd.cFileName << std::endl;
	FindNextFile(hd, &fd);
	std::cout << fd.cFileName << std::endl;
	system("pause");
	return 0;
}