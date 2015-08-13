#include <iostream>
#include <string>
#include "spider.h"



int main(int argc, char *argv[])
{
	char c[64] = {0};
	std::cout << "Please choose mode:" << std::endl<<"[ 1 ] - Direct output to a file"<< std::endl << "[ 2 ] - Input the url" <<std::endl << "[-1 ] - Quit" << std::endl;
	//std::cin >> sel;
	std::cin >> c;
	Config spider;
	while(atoi(c) != -1)
	{
		if (atoi(c) == 1)
		{
			std::cout << "Please wait......" << std:: endl;
			spider.Init();
			std::cout << "------------OK-----------" << std::endl;
			break;
		}
		else if (atoi(c) == 2)
		{
			char deurl[128] = {0};
			std::cout << "Input the url you want:(Enter 'exit' to quit)" << std::endl;
			std::cin >> deurl;
			std::string testurl = deurl;
			if (testurl == "exit")
				break;
			std::string dept;
			dept = spider.GetDepteName(testurl);
			std::cout << dept << std::endl;
		}
		else
		{
			std::cout << "Input Invalid! Please Input Again:" <<std::endl;
			std::cin >> c;
		}
	}


	system("pause");

	return 0;
}
