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
	//modify : 8/11 12:30 将类成员函数改为static，表示这个函数依赖这个类，而不依赖对象，也就是说，static函数在类加载的时候就已经分配好内存，而非static函数
	//则是在对象的产生的时候分配内存
	static std::string GetUrlHtml(const char *);
	//void DisplayHttpPage(LPCTSTR pszServerName, LPCTSTR pszFileName);
	
	static bool UTF8ToMB(std::string& , const char* , int );

	static std::string GetGateGory(const std::string &);

	static int Judge(const std::string &);

private:
	
};


#endif

