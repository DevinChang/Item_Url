#include <WinSock2.h>
#include <string>
#include <fstream>
#include <queue>
#include <map>
#include <boost/regex.hpp>
#include "spider.h"
#include "DownHtml.h"
#include "Mtverify.h"
#include "MyThreadPool.h"
#include "MyThread.h"

#pragma comment(lib, "ws2_32.lib")   


void Config::Init()
{
	//window下初始化socke	
	WSADATA WsaData;
	if (WSAStartup(MAKEWORD(2,2), &WsaData) != 0 )
	{
		return;
	}
	
	//创建存放分类好文件的目录
	CreateDirectory("./html", 0);
	std::string QueUrl;
	std::fstream Test;
	std::queue<std::string> MainQue;
	Test.open("./bugtest.txt");
	while(getline(Test, QueUrl))
	{
		std::string HtmlUrl;
		std::string DeptName;
		MainQue.push(QueUrl);
		/*
		//modify : 8/11 12:55 将类中的方法设置为静态后，就不必调用方法时再创建一个对象了。
		HtmlUrl = DownHtml::GetUrlHtml(QueUrl.c_str());
		DeptName = DownHtml::GetGateGory(HtmlUrl);
		std::ofstream File;
		File.open("./html/1.txt", std::ios::app);
		File << QueUrl << "\t" << DeptName << std::endl;
		File.close();
		*/
	}
	Test.close();
	MSG msg;
	MyThreadPool obj;
	DWORD MainThreadID = GetCurrentThreadId();
	obj.CreateThreadPool(MainThreadID);
	
	std::string DistriURL;
	int TaskCount = MainQue.size(), ResultCount = 0;
	SetTimer(NULL, 0, 10, NULL);
	while(GetMessage(&msg, NULL, 0, 0))
	{
		if (msg.message == WM_TIMER)
		{
			//
			while(obj.GetFreeThreadCount())
			{
				if (MainQue.size() > 0)
				{	
					DistriURL = MainQue.front();
					MainQue.pop();
					obj.ReceiveTask(DistriURL);
				}

			}
		}
		else if (msg.message == MSG_DEPTNAME)
		{
			ThreadData *Data = (ThreadData *)msg.wParam;
			std::ofstream File;
			File.open("./html/1.txt", std::ios::app);
			File << Data->s_URL << "\t" << Data->s_DepetName << std::endl;
			delete Data;
			File.close();
			ResultCount++;
			if (ResultCount == TaskCount)
				break;
		}
	}
		
}

std::string Config::GetDepteName(std::string &Testurl)
{
	if (Testurl.empty()) 
	{
		std::cout << "Url invalid!" << std::endl;
		return NULL;
	}
	//利用正则表达式判断url是否合法
	if (!Judgeurl(Testurl))
		return "error url";
	if (Testurl.find(".") == Testurl.npos)
		return "error url";

	//人工分类处理不准确的url
	std::map<std::string, std::string> MyWork;
	MyWork.insert(std::map<std::string, std::string>::value_type("www.baidu.com", "新闻"));
	std::map<std::string, std::string>::iterator it = MyWork.find(Testurl);
	std::string DeptName;
	if (it != MyWork.end())
	{
		DeptName = MyWork[Testurl];
		return DeptName;
	}
	//搜索类别
	std::string HtmlUrl = DownHtml::GetUrlHtml(Testurl.c_str());
	DeptName = DownHtml::GetGateGory(HtmlUrl);
	return DeptName;
}

//利用正则表达式判断url是否合法
bool Config::Judgeurl(std::string &Url)
{

	boost::regex Patten("^(http://|https://)?((?:[A-Za-z0-9]+-[A-Za-z0-9]+|[A-Za-z0-9]+)\.)+([A-Za-z]+)[/\?\:]?.*$");

	return boost::regex_match(Url, Patten);
}