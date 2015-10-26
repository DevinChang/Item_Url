#include <memory>
#include "thread.h"
#include "deptename.h"
#include "util.h"
#include "boost/smart_ptr.hpp"



void CThread::StartThread()
{
	main_thread_id_ = GetCurrentThreadId();
	thread_ = (HANDLE)_beginthreadex(NULL, 0, 
		reinterpret_cast<PBEGINTHREADEX_THREADFUNC>(CThread::ThreadFunc), 
		static_cast<LPVOID>(this), 
		0, 
		reinterpret_cast<PBGINTHREADEX_THREADID>(&thread_id_));
	//modify: 8/24 bug：线程创建完成，但线程的消息队列没有创建好，导致消息丢失。
	Sleep(100);
}

DWORD WINAPI CThread::ThreadFunc(LPVOID param)
{
	CThread *pro = reinterpret_cast<CThread *>(param);
	MSG msg;

	while (GetMessage(&msg, NULL ,0, 0))
	{
		if (msg.message == MSG_EXIT_THREAD)
			break;
		else if (msg.message == MSG_DEAL_URL)
		{
 			CDepartmentName *dept = CDepartmentName::GetInstance();
			std::string html_url = CUtil::DownLoadRecource(pro->tar_url_.c_str(), "www.baidu.com", 80);
			ThreadData *data = new ThreadData;

 			data->dept_url = pro->tar_url_;
 			data->department = dept->GetGateGory(html_url);
			data->deal = true;
			PostThreadMessage(pro->main_thread_id_, MSG_DEPTNAME, reinterpret_cast<WPARAM>(data), 0);
			pro->SetStatus(true);
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return 0;
}

bool CThread::IsFree()
{
	return isfree_;
}

void CThread::SetStatus(bool isfree)
{
	isfree_ = isfree;
}

DWORD CThread::GetThreadID()
{
	return thread_id_;	
}


void CThread::AssigTask(NodeUrl node_url)
{
	node_url_ = node_url;
	SetStatus(false);
	PostThreadMessage(thread_id_, MSG_DEAL_URL, 0, 0);
}

void CThread::AssigTask(const std::string &target_url)
{
	tar_url_ = target_url;
	SetStatus(false);
	PostThreadMessage(thread_id_, MSG_DEAL_URL, 0, 0);
}

void CThread::Destroy()
{
	PostThreadMessage(thread_id_, MSG_EXIT_THREAD, 0, 0);
}

CThread::~CThread()
{
	WaitForSingleObject(thread_, INFINITE);
	CloseHandle(thread_);
}