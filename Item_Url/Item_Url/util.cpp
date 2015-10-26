#include <Windows.h>
#include <vector>
#include <string.h>
#include "util.h"
#include "boost/algorithm/string.hpp"
#include "boost/smart_ptr.hpp"
#include "ini.h"



/*
传入url下载对应的搜索引擎的页面源码
@web_host 搜索引擎
@port 端口号
*/
std::string CUtil::DownLoadRecource(const std::string &url, const std::string &web_host, int port)
{
	//初始化socket
	WSADATA wsa_data = {0};
	int ret = WSAStartup(MAKEWORD(2, 2), &wsa_data);
	if (ret != 0)
	{
		std::cout << ret << std::endl;
		return SOCKET_STARTUP_ERROR;
	}
	SOCKET new_socket;
	new_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (new_socket == INVALID_SOCKET)
		return SOCKET_INIT_ERROR;

	struct hostent * host = gethostbyname(web_host.c_str());
	if (host == NULL)
		return SOCKET_DRRESS_ERROR;

	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	memcpy(&addr.sin_addr, host->h_addr, 4);
	if (connect(new_socket, reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) != 0)
		return SOCKET_CONNECT_ERROR;

	std::string task_url = url;
	std::string request = "GET /s?wd="+ task_url + " HTTP/1.1\r\nHOST:" + web_host + "\r\nConnection:Close\r\n\r\n";
	if (send(new_socket, request.c_str(), request.size(), 0) == SOCKET_ERROR)
		return SOCKET_SEND_ERROR;

	std::string resource;
	char page_buf[1024] = {0};
	do
	{
		ret = recv(new_socket, page_buf, 1024, 0);
		if (ret > 0)
			resource.append(page_buf, ret);
		else if (ret == SOCKET_ERROR)
			std::cout << "Recv failed: " << WSAGetLastError() << std::endl;
	}while (ret > 0);
	closesocket(new_socket);
	WSACleanup();
	return resource;
}

bool CUtil::UTF8ToMB(const std::string &src, std::string& dest)    
{    
	// convert an UTF8 string to widechar     
	int length = MultiByteToWideChar(CP_UTF8, 0, src.c_str(), src.size(), NULL, 0);    

	WCHAR* wide_char = NULL;
	wide_char = new WCHAR[length];
	if (wide_char == NULL)
	{
		std::cout << "new memroy err!" << std::endl;
		return false;
	}
	int ret = MultiByteToWideChar(CP_UTF8, 0, src.c_str(), src.size(), wide_char, length);    

	if(ret != length)    
	{    
		delete[] wide_char;    
		return false;    
	}    
	// convert an widechar string to Multibyte     
	int mb_length = WideCharToMultiByte(CP_ACP, 0, wide_char, length, NULL, 0, NULL, NULL);    
	if (mb_length <=0)       
		return false;    

	dest.resize(mb_length);    
	ret = WideCharToMultiByte(CP_ACP, 0, wide_char, length, &*dest.begin(), mb_length, NULL, NULL);    
	delete[] wide_char;    

	if(ret != mb_length)    
	{    
		dest.clear();    
		return false;    
	}    
	return true;    
}  

std::vector<std::string> CUtil::LoadSectionNames(const std::string &ini_file_name)
{
	CIniFile ini;
	ini.SetIniFilePath(ini_file_name);
	return ini.GetSectionNames();
}


std::string CUtil::LoadSectionKeyValue(const std::string &section, const std::string &key, const std::string &ini_file_name)
{
	CIniFile ini;
	ini.SetIniFilePath(ini_file_name);
	return ini.GetValueKey(section, key);
}
