#include "WinInfo.h"
#include "VirualCheck.h"


int main(void)
{
	getchar();
	if (CVirualCheck::IsVirtualPC())
		printf("In Virtual OS!!\n");
	else
		printf("In Native OS!!\n");

	std::string hostip;

	char *ip = NULL;
	WSADATA        wsaData;

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//printf("%s\n", (ip = CVirualCheck::GetHostIP()) ? ip : "faild");

	WSACleanup();
	
	std::vector<std::string> vct_graphics;

	/*
	//通过WMI来获取显卡信息(速度略慢)
	std::string graphic_name;
	DWORD graphic_count = 0;
	CVirualCheck::GetGraphicInfo(&graphic_count, graphic_name);
	CWmiInfo wmi;
	wmi.GetSingleItemInfo("Win32_VideoController", "Description", vct_graphics);
	for (int i = 0; i < vct_graphics.size(); ++i)
	{
		std::cout << vct_graphics[i] << std::endl;
	}
	vct_graphics.clear();
	*/

	//通过遍历系统信息获取显卡信息
	//vct_graphics = CVirualCheck::GetGraphicsType();
	//for (int i = 0; i < vct_graphics.size(); ++i)
	//{
	//	std::cout << "GraphicsInfo: " << vct_graphics[i] << std::endl;
	//}
	system("pause");
	return 0;
}