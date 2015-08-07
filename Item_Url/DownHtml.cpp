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

//��AC��ģƥ���㷨�Ż�Ϊ����һ��str���ɰ����йؼ��ֵĴ���ͳ�Ƴ���
//modify: 8/4/17:53 �����飬AC��ģƥ���㷨���㷨�ﲻ���Ż���Ŀ�ġ�
int DownHtml::Category(const std::string &Str)
{
	AhoCorasick AhoCk;
	string ss[12] = {"����", "����", "����", "����","��Ϸ", "��Ƶ", "����", "����", "��Ƹ", "ͨ��", "����", "����"};
	vector<string>  ptns(ss, ss+12);
	AhoCk.ac_creat_goto_table(ptns);
	AhoCk.ac_creat_fail_table();

	int ret = AhoCk.ac_search(Str);

	AhoCk.ac_convert_to_DFA();

	return ret;
}
//��ÿ�����ͳ�ƴ���
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
//�ҳ������ļ������е�section
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
			//�����һ��Ԫ�ؽ������
			SecName[j++] = tmp;
			break;
		}
	}
	*n = j;
	return SecName;
}

//��ÿ��section�µ�value���м���
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

//�ж���ҵ���
int DownHtml::Judge(const std::string &Str) //���Ż�
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

	//��ȡini�ļ�����section��ֵ�����س���ÿ��section��������NULL��β�ġ�
	//modify: 8/7 17:00 ��ÿ�������Ӷ���ؼ��֣���ini�ļ�����ÿ���ؼ��֡�
	GetPrivateProfileSectionNames(secbuf, sizeof(secbuf), "./bin/initkey.ini");
	keyBuf = ExtractSection(secbuf, sizeof(secbuf), &n);
	//��ȡָ��section��key_value��ֵ
	for (int i = 0; i < n; i++)
	{
		GetPrivateProfileSection(keyBuf[i].c_str(), valuebuf, sizeof(valuebuf), "./bin/initkey.ini");
		int buflen = strlen(valuebuf);
		a[i] = SearchValue(valuebuf, Str, buflen);
	}

	//�ͷ��ڴ�
	delete[]keyBuf;
	
	//�ж��������ĸ�Ԫ����󣬷������±�
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
	//modify: 8/25 10:34 ���̵߳��Ż�Ҫ�����￪ʼ
	if (UTF8ToMB(uf8, Url.c_str(), strlen(Url.c_str())))
	{
		deptno = Judge(uf8);
		//deptno = Category(uf8);
	}

	//�����ʵ�
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

//ץȡҳ��Դ�벢�����ֵ䷵�ز�������
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
			ZeroMemory(p, sizeof(1024)); //���ֽڣ����ֽ�
			if(!InternetReadFile(hInternetUrl, p, 1024, &ReadDataLength))
				return NULL;
			resouce.append(p, ReadDataLength);
			
		}while(ReadDataLength > 0);
		std::string uf8;
		int deptno = 0;
		
		//modify: 8/25 10:34 ���̵߳��Ż�Ҫ�����￪ʼ
		//deptname = GetGateGory(resouce);

	} while (0);
	InternetCloseHandle(hInternetUrl);
	InternetCloseHandle(hInternet);
	return resouce;
}


// UTF8����תΪ���ֽڱ���    
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
