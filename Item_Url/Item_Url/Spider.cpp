#include <WinSock2.h>
#include <string>
#include <string.h>
#include <fstream>
#include <queue>
#include <map>
#include <algorithm>
#include "spider.h"
#include "threadpool.h"
#include "deptename.h"
#include "util.h"



#pragma comment(lib, "ws2_32.lib")   




void CSpider::Init(const std::string &deal_url)
{
	if (!UrlIsLegal(deal_url))
		return;
	stroe_vec_.clear();
	NodeUrl tmp_url;
	tmp_url.deal_url = deal_url;
	tmp_url.isdeal = false;
	url_vec_.clear();
	stroe_vec_.push_back(tmp_url);
	url_vec_.push_back(deal_url);
	method_ = READ_CMD;
}

void CSpider::Init()
{
	//创建存放分类好文件的目录
	CreateDirectory("./html", 0);
	std::string que_url;
	std::fstream task;
	//Test.open("./bin/taskurl.txt");//这个是全部任务，为了测试多线程的效果，将采用testurl文本。
	task.open("./bin/bugtest.txt");
	if (task.fail())
		std::cerr << "Error: " << strerror(errno);
	while(getline(task, que_url))
	{
		
		NodeUrl tmp_url;
		tmp_url.deal_url = que_url;
		tmp_url.isdeal = false;
		stroe_vec_.push_back(tmp_url);
		
		url_vec_.push_back(que_url);
	}
	task.close();
	method_ = READ_FILE;
}

void CSpider::BeginTask(int thread_count)
{	
	MSG msg;
	CThreadPool obj;
	obj.CreateThreadPool(thread_count);
	std::vector<std::string>::iterator it = url_vec_.begin();
	int task_count = url_vec_.size(), result_count = 0;
	int timeout_count = 0;
	std::string result_url;
	SetTimer(NULL, 0, 10, NULL);
	while(GetMessage(&msg, NULL, 0, 0))
	{
		if (msg.message == WM_TIMER)
		{
			//BUG : 8/13 19:16 当ResultCount为26时，MainQue为空，造成这里阻塞
			while(obj.GetFreeThreadCount())
			{
				if (it != url_vec_.end())
				{
					obj.ReceiveTask(*it);
					it++;
				}
				if (it == url_vec_.end())
				{
					timeout_count++;
					break;
				}
			}
		}
		else if (msg.message == MSG_DEPTNAME)
		{
			boost::shared_ptr<ThreadData> data(reinterpret_cast<ThreadData *>(msg.wParam));
			if (method_)
			{
				result_url.append(data->dept_url + "\t" + data->department + "\n");
				for (std::vector<NodeUrl>::iterator node_it = stroe_vec_.begin(); node_it != stroe_vec_.end(); node_it++)
				{
					if ((*node_it).deal_url == data->dept_url)
						(*node_it).isdeal = data->deal;
				}
				result_count++;
				if (result_count == task_count)
					break;
			}
			else
			{
				ThreadData *data = reinterpret_cast<ThreadData *>(msg.wParam);
				std::cout <<  data->dept_url << "\t" << data->department << std::endl;
				break;
			}
		}
		if (timeout_count > TIME_OUT)
		{
			std::vector<NodeUrl>::iterator it = stroe_vec_.begin();
			for (it = stroe_vec_.begin(); it != stroe_vec_.end(); it++)
			{
				if (!(*it).isdeal)
					std::cout << (*it).deal_url << " 未处理" << std::endl;
			}
			break;
		}
	}
	if (method_)
	{
		std::ofstream file;
		file.open("./html/1.txt", std::ios::app);
		if (file.fail())
			std::cerr << "Error: " << strerror(errno);
		//file << data->dept_url << "\t" << data->department << std::endl;
		file << result_url <<std::endl;
		file.close();
	}
}



//利用正则表达式判断url是否合法
bool CSpider::UrlIsLegal(const std::string &url)
{
	boost::regex patten( "^(http://|https://)?((?:[A-Za-z0-9]+-[A-Za-z0-9]+|[A-Za-z0-9]+)\\.)+([A-Za-z]+)[/\?\\:]?.*$");
	//boost::regex patten("^((http)://)?\w+\.\w+\.\w+");
	return boost::regex_match(url, patten);
}