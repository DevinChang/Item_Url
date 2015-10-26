#pragma once

#include <iostream>
#include <string>


#define SECTION_DEPT_COUNT 12
#define ERROR_URL "error url!"

#define ERROR_MYSTRING  "error string"
#define TIME_OUT 500
#define MSG_DEPTNAME 101
#define MSG_DEAL_URL 100
#define MSG_DEPTNAME 101
#define MSG_EXIT_THREAD 102
#define THREAD_POOL_SIZE 10
#define MSG_DEAL_URL 100

#define ERROR_MYSTRING  "error string"
#define SOCKET_STARTUP_ERROR "WSAStartup Error! "
#define SOCKET_INIT_ERROR  "Socket Init Error! "
#define SOCKET_DRRESS_ERROR  "Can not Find Adrress! "
#define SOCKET_CONNECT_ERROR  "Connect Socket Error! "
#define SOCKET_SEND_ERROR  "Send Error! "

class CUtil
{
public:
	static std::string DownLoadRecource(const std::string &, const std::string &, int port);
	static bool UTF8ToMB(const std::string &, std::string&);
	static std::vector<std::string> LoadSectionNames(const std::string &);
	static std::vector<std::string> LoadSectionAllValue(const std::string &);
	static std::string LoadSectionKeyValue(const std::string &, const std::string &, const std::string &);
};

