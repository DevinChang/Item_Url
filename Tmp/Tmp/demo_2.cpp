#include <iostream>
#include <Windows.h>
#include "boost/smart_ptr/shared_ptr.hpp"

int main2(int argc, char **argv)
{
	
	//ShellExecute(0,"runas", LPCSTR("cmd.exe"),LPCSTR("schtasks /run /tn \"\\Microsoft\\Windows\\TextServicesFramework\\MsCtfMonitor\""),"",SW_HIDE);
	//WinExec("cmd /c schtasks /run /tn \"\\Microsoft\\Windows\\TextServicesFramework\\MsCtfMonitor\" & pause", SW_SHOW);
	//FILE *f;
	//f=fopen("tmp.bat","r");
	//fprintf(f,"runas /noprofile /user:mymachine\\administrator \"cmd /c \\\"\\Microsoft\\Windows\\TextServicesFramework\\MsCtfMonitor\"""\n");
	//fclose(f);
	//WinExec("cmd /c pause",SW_HIDE);
	//remove("tmp.bat");
	//system("pause");
	
	boost::shared_ptr<char> buffer(new char[128]);
	//����ָ���ṩ��һ��ֱ�ӷ���ԭʼ�ڴ�ķ�����ͨ��������ĳ�Ա����get()�����ԶԻ���ָ����й���
	std::cout << buffer.get();
	system("pause");
	return 0;
}