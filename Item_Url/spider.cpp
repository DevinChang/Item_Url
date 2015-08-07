#include <WinSock2.h>
#include <string>
#include <fstream>
#include <queue>
#include <map>
#include <boost/regex.hpp>
#include "spider.h"
#include "DownHtml.h"

#pragma comment(lib, "ws2_32.lib")   

#define THREAD_NUM 5


void Config::Init()
{
	//window下初始化socke	
	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(2,2), &wsadata) != 0 )
	{
		return;
	}
	
	//创建存放分类好文件的目录
	CreateDirectory("./html", 0);
	std::string queurl;
	std::fstream test;
	std::queue<std::string> que;
	test.open("./bugtest.txt");
	while(getline(test, queurl))
	{
		//std::cout << queurl << std::endl;
		//que.push(queurl);
		std::string sengine = "https://www.baidu.com/s?&wd=";
		std::string surl = sengine + queurl;
		std::string htmlurl;
		std::string deptname;
		DownHtml down;

		htmlurl = down.GetUrlHtml(surl.c_str());
		deptname = down.GetGateGory(htmlurl);
		
		std::ofstream file;
		file.open("./html/1.txt", std::ios::app);
		file << queurl << "\t" << deptname << std::endl;
		file.close();
	
	}
	test.close();


	//modify: 8/5 11:15 欲实现下载源码与解析源码业务分离
	//HANDLE Getthread = CreateThread(NULL, 0, GetHtml, str, NULL, NULL);
	//想让这两个线程这样工作：Getthread负责根据url抓取页面源码，存到一个容器里。Anythread根据容器里的源码匹配出相应的部门名称
	//HANDLE Anythread = CreateThread(NULL, 0, AnyHtml, NULL, NULL, NULL);
	//modify: 8/5 17:27 优化下载url，利用多个线程来下载整个文件中的url 
	/*
	for (int i = 0; i < THREAD_NUM; i++)
	{
		HANDLE m_thread = CreateThread()
	}
	*/
	

}

std::string Config::GetDepteName(std::string &Testurl)
{
	if (Testurl.empty()) 
	{
		std::cout << "Url invalid!" << std::endl;
		return NULL;
	}
	std::string deptname;

	//利用正则表达式判断url是否合法
	if (!Judgeurl(Testurl))
		return "error url";
	if (Testurl.find(".") == Testurl.npos)
		return "error url";

	//人工分类处理不准确的url
	std::map<std::string, std::string> mawork;
	mawork.insert(std::map<std::string, std::string>::value_type("www.baidu.com", "新闻"));
	std::map<std::string, std::string>::iterator it = mawork.find(Testurl);
	if (it != mawork.end())
	{
		deptname = mawork[Testurl];
		return deptname;
	}
	//添加搜索引擎
	std::string sengine = "https://www.baidu.com/s?&wd=";
	std::string surl = sengine + Testurl;
	std::string htmlurl;
	//std::string deptname;
	DownHtml down;
	htmlurl = down.GetUrlHtml(surl.c_str());
	deptname = down.GetGateGory(htmlurl);
	return deptname;
}

//利用正则表达式判断url是否合法
bool Config::Judgeurl(std::string &Url)
{
	//(http://)?([\w-]+\.)+[\w-]+(/[\w-./?%&=]*)?
	/*
	if (std::regex_match(url,std::regex("(http://)?([\w-]+\.)+[\w-]+(/[\w-./?%&=]*)")))
	{
		return true;
	}
	(\\w+)://((\\w+\\.)*\\w+)((/\\w*)*)(/\\w+\\.\\w+)?
	*/
	boost::regex patten("^(http://|https://)?((?:[A-Za-z0-9]+-[A-Za-z0-9]+|[A-Za-z0-9]+)\.)+([A-Za-z]+)[/\?\:]?.*$");
	if (boost::regex_match(Url, patten))
		return true;
	return false;
}