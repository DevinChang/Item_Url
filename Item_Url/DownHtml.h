#ifndef __DOWNHTML_H__
#define __DOWNHTML_H__

#include <string>
#include <vector>

#define BUFF_MAX_LENGTH 1048576
#define ERROR_MYSTRING  "error string"
#define SOCKET_1_ERROR "WSAStartup Error! "
#define SOCKET_2_ERROR  "Socket Init Error! "
#define SOCKET_3_ERROR  "Can not Find Adrress! "
#define SOCKET_4_ERROR  "Connect Socket Error! "
#define SOCKET_5_ERROR  "Send Error! "

class DownHtml
{
public:
	//modify : 8/11 12:30 �����Ա������Ϊstatic����ʾ���������������࣬������������Ҳ����˵��static����������ص�ʱ����Ѿ�������ڴ棬����static����
	//�����ڶ���Ĳ�����ʱ������ڴ�
	static std::string GetUrlHtml(const char *);
	//void DisplayHttpPage(LPCTSTR pszServerName, LPCTSTR pszFileName);
	
	static bool UTF8ToMB(std::string& , const char* , int );

	static std::string GetGateGory(const std::string &);

	static int Judge(const std::string &);

private:
	
};


#endif

