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

//用AC多模匹配算法优化为遍历一次str即可把所有关键字的次数统计出来
//modify: 8/4/17:53 经检验，AC多模匹配算法的算法达不到优化的目的。
int DownHtml::Category(const std::string &Str)
{
	AhoCorasick AhoCk;
	string ss[12] = {"新闻", "购物", "银行", "集团","游戏", "视频", "教育", "政府", "招聘", "通信", "健康", "旅游"};
	vector<string>  ptns(ss, ss+12);
	AhoCk.ac_creat_goto_table(ptns);
	AhoCk.ac_creat_fail_table();

	int ret = AhoCk.ac_search(Str);

	AhoCk.ac_convert_to_DFA();

	return ret;
}
//对每个类别统计次数
int FindDeptNum(const std::string &Url, const std::string &Dept)
{
	int pos = 0;
	int count = 0;
	while(pos >= 0)
	{
		pos = Url.find(Dept, pos + 8);
		if (pos > 0)
			count++;
	}
	return count;
}
//找出配置文件中所有的section
std::string *ExtractSection(const char *Buf, int Len, int *n)
{
	if (Buf == NULL);
	std::string *SecName = new std::string[32];
	char tmp[16] = {0};
	int k = 0;
	int i = 0;
	int j = 0;
	//pos = strstr(buf, "0");
	for (; i < Len; i++)
	{
		if (Buf[i] != 0)
			tmp[k++] = Buf[i];
		else if (Buf[i + 1] != 0)
		{	
			SecName[j++] = tmp;
			//std::cout << SecName[j];
			//i++;
			memset(tmp, 0, sizeof(tmp));
			k = 0;
			
		}
		else
		{
			//将最后一个元素进入队列
			SecName[j++] = tmp;
			break;
		}
	}
	*n = j;
	return SecName;
}

//对每个section下的value进行检索
int SearchValue(const char *Buf, const std::string &Url, int Len)
{
	std::string value[16];
	char tmp[16] = {0};
	int k = 0;
	int j = 0;
	int v = 0;
	for (int i = 0; i < Len; i++)
	{
		while(Buf[j] != 32 && j < Len)
			tmp[k++] = Buf[j++];
		value[v++] = tmp;
		i = j;
		k = 0;
		j++;
	}
	int num = 0;
	int max = 0;
	for (int i = 0; i < v; i++)
	{
		num = FindDeptNum(Url, value[i]);
		max += num;
	}
	return max;
}

//判断行业类别
int DownHtml::Judge(const std::string &Str) //待优化
{
	int pos = 0;
	int count = 0;
	int a[12] = {0};

	std::string *keyBuf;

	char buf[32] = {0};
	char secbuf[128] = {0};
	char valuebuf[32] = {0};
	//DWORD num;
	int n = 0;

	//获取ini文件所有section的值，返回出的每个section是由两个NULL结尾的。
	//modify: 8/7 17:00 对每个类别添加多个关键字，用ini文件读出每个关键字。
	GetPrivateProfileSectionNames(secbuf, sizeof(secbuf), "./bin/initkey.ini");
	keyBuf = ExtractSection(secbuf, sizeof(secbuf), &n);
	//获取指定section下key_value的值
	for (int i = 0; i < n; i++)
	{
		GetPrivateProfileSection(keyBuf[i].c_str(), valuebuf, sizeof(valuebuf), "./bin/initkey.ini");
		int buflen = strlen(valuebuf);
		a[i] = SearchValue(valuebuf, Str, buflen);
	}

	//释放内存
	delete[]keyBuf;
	
	//判断数组中哪个元素最大，返回其下标
	int k = 0;
	int max = a[0];
	for (int i = 0; i < 12; i++)
	{
		if (a[i] > max)
		{
			max = a[i];
			k = i;
		}
	}
	return k;
}

std::string DownHtml::GetGateGory(const std::string &Url)
{
	std::string deptname;
	std::string uf8;
	int deptno = 0;
	//modify: 8/25 10:34 多线程的优化要从这里开始
	if (UTF8ToMB(uf8, Url.c_str(), strlen(Url.c_str())))
	{
		deptno = Judge(uf8);
		//deptno = Category(uf8);
	}

	//建立词典
	std::map<int, std::string> m;
	std::string mapstr;
	std::fstream config;
	config.open("./Config.txt");
	int i = 0;
	while(getline(config, mapstr))
	{
		m.insert(std::map<int, std::string>::value_type(i, mapstr));
		i++;
	}
	std::map<int, std::string>::iterator it = m.find(deptno);
	if (it != m.end())
		deptname = m[deptno];
	return deptname;
}

//抓取页面源码并根据字典返回部门名称
std::string DownHtml::GetUrlHtml(const char *Url)
{
	DWORD err;
	std::string deptname;
	std::string resouce;
	HINTERNET hInternet = InternetOpen("Mozilla/5.0 (Windows NT 6.1; WOW64; rv:39.0) Gecko/20100101 Firefox/39.0", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, NULL);
	HINTERNET hInternetUrl = InternetOpenUrl(hInternet, Url, NULL, NULL, INTERNET_FLAG_NO_CACHE_WRITE, NULL); 
	do 
	{
		if (hInternet == NULL) break;
		if (hInternetUrl == NULL)
		{
			err = GetLastError();
			printf("%d\n", err);
			break;
		}
		
		char p[1024] = {0};
		DWORD ReadDataLength = 0;
		bool bRet = true;
		do
		{
			ZeroMemory(p, sizeof(1024)); //多字节，宽字节
			if(!InternetReadFile(hInternetUrl, p, 1024, &ReadDataLength))
				return NULL;
			resouce.append(p, ReadDataLength);
			
		}while(ReadDataLength > 0);
		std::string uf8;
		int deptno = 0;
		
		//modify: 8/25 10:34 多线程的优化要从这里开始
		//deptname = GetGateGory(resouce);

	} while (0);
	InternetCloseHandle(hInternetUrl);
	InternetCloseHandle(hInternet);
	return resouce;
}


// UTF8编码转为多字节编码    
bool DownHtml::UTF8ToMB(std::string& Pmb, const char* Pu8, int Utf8Len)    
{    
	// convert an UTF8 string to widechar     
	int nLen = MultiByteToWideChar(CP_UTF8, 0, Pu8, Utf8Len, NULL, 0);    

	WCHAR* lpszW = NULL;    
	try    
	{    
		lpszW = new WCHAR[nLen];    
	}    
	catch(std::bad_alloc &memExp)    
	{    
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
