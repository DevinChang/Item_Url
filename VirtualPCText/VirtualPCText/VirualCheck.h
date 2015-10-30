#pragma once

#include <iostream>
#include <WinSock2.h>
#include <excpt.h>
#include <string>
#include <vector>
#include "windef.h"

class CVirualCheck
{
public:
	//判断是否为虚拟机，若返回为true则为虚拟机
	static bool IsVirtualPC();
private:
	//通过VMware上不能执行的一些特殊指令来判断，这种方法只能判断VMWare
	static bool IsSandboxed();

	//通过Model Number(硬盘的型号)来判断，VMWare虚拟机上的ModelNumber通常有"vmware,virtual"等字符串
	//VMBox上的ModelNumber含有"vbox"等字符串.
	static bool IsInsideVMWare();

	//获取本地IP
	static char* GetHostIP();

	//通过WMI获取显卡信息
	static void GetGraphicInfo(DWORD *count, std::string &grathic_name);
	//通过遍历系统信息获取显卡信息
	static std::vector<std::string> GetGraphicsType();

	static bool IsVirtualGraphicCard();
};

