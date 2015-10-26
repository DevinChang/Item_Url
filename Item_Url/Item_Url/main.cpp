#include <iostream>
#include <string>
#include "spider.h"


int main(int argc, char *argv[])
{
	char c[64] = {0};
	std::cout << "Please choose mode:" << std::endl<<"[ 1 ] - Direct output to a file"<< std::endl << "[ 2 ] - Input the url" <<std::endl << "[-1 ] - Quit" << std::endl;
	std::cin >> c;
	CSpider spider;
	while(atoi(c) != -1)
	{
		if (atoi(c) == 1)
		{
			std::cout << "Warning: This operation will cost you a lot of time! Enter 'Y' to continue!(Enter any key to quit!)" << std::endl;
			char input;
			std::cin >> input;
			
			if (input == 'y' || input == 'Y')
			{
				std::cout << "Please wait......" << std:: endl;
				int thread_count = 10;
				spider.Init();
				spider.BeginTask(thread_count);
				std::cout << "------------OK-----------" << std::endl;
				break;
			}
			else 
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
			spider.Init(testurl);
			spider.BeginTask();
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
