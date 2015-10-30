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
	//�ж��Ƿ�Ϊ�������������Ϊtrue��Ϊ�����
	static bool IsVirtualPC();
private:
	//ͨ��VMware�ϲ���ִ�е�һЩ����ָ�����жϣ����ַ���ֻ���ж�VMWare
	static bool IsSandboxed();

	//ͨ��Model Number(Ӳ�̵��ͺ�)���жϣ�VMWare������ϵ�ModelNumberͨ����"vmware,virtual"���ַ���
	//VMBox�ϵ�ModelNumber����"vbox"���ַ���.
	static bool IsInsideVMWare();

	//��ȡ����IP
	static char* GetHostIP();

	//ͨ��WMI��ȡ�Կ���Ϣ
	static void GetGraphicInfo(DWORD *count, std::string &grathic_name);
	//ͨ������ϵͳ��Ϣ��ȡ�Կ���Ϣ
	static std::vector<std::string> GetGraphicsType();

	static bool IsVirtualGraphicCard();
};

