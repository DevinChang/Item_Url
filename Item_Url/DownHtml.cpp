#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <Windows.h>
#include <WinInet.h>
#include <fstream>
#include <map>

#include "DownHtml.h"
#include "AhoCorasick.h"

#pragma comment(lib,"Wininet.lib") 


//对每个类别统计次数
int FindDeptNum(const std::string &Url, const std::string &Dept)
{
	int Pos = 0;
	int mCount = 0;
	while(Pos >= 0)
	{
		Pos = Url.find(Dept, Pos + 8);
		if (Pos > 0)
			mCount++;
	}
	return mCount;
}
//找出配置文件中所有的section
std::string *ExtractSection(const char *Buf, int Len, int *Num)
{
	if (Buf == NULL) return NULL;
	std::string *SecName = new std::string[32];
	char Tmp[16] = {0};
	int k = 0;
	int i = 0;
	int j = 0;
	for (; i < Len; i++)
	{
		if (Buf[i] != 0)
			Tmp[k++] = Buf[i];
		else if (Buf[i + 1] != 0)
		{	
			SecName[j++] = Tmp;
			//std::cout << SecName[j];
			//i++;
			memset(Tmp, 0, sizeof(Tmp));
			k = 0;
			
		}
		else
		{
			//将最后一个元素进入队列
			SecName[j++] = Tmp;
			break;
		}
	}
	*Num = j;
	return SecName;
}

//对每个section下的value进行检索
int SearchValue(const char *Buf, const std::string &Url, int Len)
{
	std::string Value[16];
	char Tmp[16] = {0};
	int k = 0;
	int j = 0;
	int v = 0;
	for (int i = 0; i < Len; i++)
	{
		while(Buf[j] != 32 && j < Len)
			Tmp[k++] = Buf[j++];
		Value[v++] = Tmp;
		i = j;
		k = 0;
		j++;
	}
	int Num = 0;
	int Max = 0;
	for (int i = 0; i < v; i++)
	{
		Num = FindDeptNum(Url, Value[i]);
		Max += Num;
	}
	return Max;
}

//判断行业类别
int DownHtml::Judge(const std::string &Str) //待优化
{
	int Arr[12] = {0};
	//??
	char Secbuf[128] = {0};
	char Valuebuf[32] = {0};
	
	int Num = 0;

	//获取ini文件所有section的值，返回出的每个section是由两个NULL结尾的。
	//modify: 8/7 17:00 对每个类别添加多个关键字，用ini文件读出每个关键字。
	GetPrivateProfileSectionNames(Secbuf, sizeof(Secbuf), "./bin/initkey.ini");
	std::string *KeyBuf = ExtractSection(Secbuf, sizeof(Secbuf), &Num);
	if (KeyBuf == NULL)
		return -1;
	//获取指定section下key_value的值
	for (int i = 0; i < Num; i++)
	{
		GetPrivateProfileSection(KeyBuf[i].c_str(), Valuebuf, sizeof(Valuebuf), "./bin/initkey.ini");
		int Buflen = strlen(Valuebuf);
		Arr[i] = SearchValue(Valuebuf, Str, Buflen);
	}

	//释放内存
	delete[]KeyBuf;
	
	//判断数组中哪个元素最大，返回其下标
	int k = 0;
	int MaxNumber = Arr[0];
	for (int i = 0; i < 12; i++)
	{
		if (Arr[i] > MaxNumber)
		{
			MaxNumber = Arr[i];
			k = i;
		}
	}
	
	return k;
}

std::string DownHtml::GetGateGory(const std::string &Url)
{
	std::string Deptname;
	std::string Uf8;
	int Deptno = 0;
	if (UTF8ToMB(Uf8, Url.c_str(), strlen(Url.c_str())))
	{
		Deptno = Judge(Uf8);
		if (Deptno == -1)
			return ERROR_MYSTRING;
	}

	//建立词典
	std::string MapStr;
	std::map<int, std::string> MyMap;
	std::fstream mConfig;
	mConfig.open("./Config.txt");
	int i = 0;
	while(getline(mConfig, MapStr))
	{
		MyMap.insert(std::map<int, std::string>::value_type(i, MapStr));
		i++;
	}
	std::map<int, std::string>::iterator it = MyMap.find(Deptno);
	if (it != MyMap.end())
		Deptname = MyMap[Deptno];
	
	return Deptname;
}

#if 0
std::string DownHtml::GetUrlHtml(const char *Url)
{
	DWORD SockErr;
	std::string Resouce;
	HINTERNET hInternet = InternetOpen("Mozilla/5.0 (Windows NT 6.1; WOW64; rv:39.0) Gecko/20100101 Firefox/39.0", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, NULL);
	HINTERNET hInternetUrl = InternetOpenUrl(hInternet, Url, NULL, NULL, INTERNET_FLAG_NO_CACHE_WRITE, NULL); 
	do 
	{
		if (hInternet == NULL) break;
		if (hInternetUrl == NULL)
		{
			SockErr = GetLastError();
			std::cout << SockErr << std::endl;
			break;
		}

		char Tmp[1024] = {0};
		DWORD ReadDataLength = 0;
		bool bRet = true;
		do
		{
			ZeroMemory(Tmp, sizeof(1024)); //多字节，宽字节
			if(!InternetReadFile(hInternetUrl, Tmp, 1024, &ReadDataLength))
				return NULL;
			Resouce.append(Tmp, ReadDataLength);

		}while(ReadDataLength > 0);

	} while (0);
	InternetCloseHandle(hInternetUrl);
	InternetCloseHandle(hInternet);
	return Resouce;
}
#endif

//抓取页面源码并根据字典返回部门名称
//modify : 8/12 11:00 将WININET改成SOCKET从网页抓取源码
std::string DownHtml::GetUrlHtml(const char *Url)
{
	//初始化socket
	WSADATA WsaData = {0};
	int Ret = WSAStartup(MAKEWORD(2, 2), &WsaData);
	if (Ret != 0)
	{
		std::cout << Ret << std::endl;
		return SOCKET_1_ERROR;
	}
	SOCKET MySocket;
	MySocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (MySocket == -1 || MySocket == -2)
	{
		return SOCKET_2_ERROR;
	}
	struct hostent * Host = gethostbyname("www.baidu.com");
	if (Host == NULL)
	{
		return SOCKET_3_ERROR;
	}
	SOCKADDR_IN mAddr;
	mAddr.sin_family = AF_INET;
	mAddr.sin_port = htons(80);
	memcpy(&mAddr.sin_addr, Host->h_addr, 4);
	if (connect(MySocket, (sockaddr *)&mAddr, sizeof(mAddr)) != 0)
	{
		return SOCKET_4_ERROR;
	}
	std::string TargetUrl = Url;
	std::string Request = "GET /s?wd="+ TargetUrl + " HTTP/1.1\r\nHOST:www.baidu.com\r\nConnection:Close\r\n\r\n";
	if (send(MySocket, Request.c_str(), Request.size(), 0) == SOCKET_ERROR)
	{
		return SOCKET_5_ERROR; 
	}
	char *PageBuf = new char[BUFF_MAX_LENGTH];
	if (PageBuf == NULL)
	{
		std::cout << "New Memory Error! " << std::endl;
	}
	memset(PageBuf, 0, sizeof(PageBuf));
	
	int ByteRead = 0;
	int ret = 1;
	while (ret > 0)
	{
		ret = recv(MySocket, PageBuf + ByteRead, BUFF_MAX_LENGTH - ByteRead, 0);
		if (ret > 0)
			ByteRead += ret;
		if (BUFF_MAX_LENGTH - ByteRead < 100)
		{
			std::cout << "Realloc Memory!" << std::endl;
			PageBuf = (char *)realloc(PageBuf, BUFF_MAX_LENGTH);
		}
	}
	PageBuf[ByteRead] = 0;
	std::string Resouce = PageBuf;
	delete[] PageBuf;
	PageBuf = NULL;
	WSACleanup();
	return Resouce;
}


// UTF8编码转为多字节编码    
bool DownHtml::UTF8ToMB(std::string& Pmb, const char* Pu8, int Utf8Len)    
{    
	// convert an UTF8 string to widechar     
	int nLen = MultiByteToWideChar(CP_UTF8, 0, Pu8, Utf8Len, NULL, 0);    

	WCHAR* lpszW = NULL;
	/*
	try    
	{    
		lpszW = new WCHAR[nLen];    
	}   
	catch(std::bad_alloc &memExp)    
	{    
		return false;    
	}    
	*/
	lpszW = new WCHAR[nLen];
	if (lpszW == NULL)
	{
		std::cout << "new memroy err!" << std::endl;
		return false;
	}
	int nRtn = MultiByteToWideChar(CP_UTF8, 0, Pu8, Utf8Len, lpszW, nLen);    

	if(nRtn != nLen)    
	{    
		delete[] lpszW;    
		return false;    
	}    
	// convert an widechar string to Multibyte     
	int MBLen = WideCharToMultiByte(CP_ACP, 0, lpszW, nLen, NULL, 0, NULL, NULL);    
	if (MBLen <=0)    
	{    
		return false;    
	}    
	Pmb.resize(MBLen);    
	nRtn = WideCharToMultiByte(CP_ACP, 0, lpszW, nLen, &*Pmb.begin(), MBLen, NULL, NULL);    
	delete[] lpszW;    

	if(nRtn != MBLen)    
	{    
		Pmb.clear();    
		return false;    
	}    
	return true;    
}    
