#include "MyThread.h"
#include "DownHtml.h"



void MyThread::StartThread(DWORD MainThrID)
{
	ThreadData SendData;
	m_MainThrID = MainThrID;
	m_hThread = (HANDLE)_beginthreadex(NULL, 0, 
		(PBEGINTHREADEX_THREADFUNC)MyThread::ThreadFunc, 
		(LPVOID)this, 
		0, 
		(PBGINTHREADEX_THREADID)&m_ThreadID);
}

DWORD WINAPI MyThread::ThreadFunc(LPVOID param)
{
	MyThread *pro = (MyThread *)param;
	MSG msg;
	while (GetMessage(&msg, NULL ,0, 0))
	{
		if (msg.message == WM_QUIT)
			break;
		else if (msg.message == MSG_DEAL_URL)
		{
			//SetStatus(true);
			std::string HtmlUrl = DownHtml::GetUrlHtml(pro->m_MyUrl.c_str());;
			ThreadData *Data = new ThreadData;
			Data->s_URL = pro->m_MyUrl;
			Data->s_DepetName = DownHtml::GetGateGory(HtmlUrl);
			PostThreadMessage(pro->m_MainThrID, MSG_DEPTNAME, (WPARAM)Data, 0);
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

DWORD MyThread::ThreadMemberFunc(const std::string &DealUrl)
{
	MSG msg;
	std::string HtmlUrl;
	std::string *DeptName = new std::string;
	while (GetMessage(&msg, NULL ,0, 0))
	{
		if (msg.message == WM_QUIT)
			break;
		else if (msg.message == MSG_DEAL_URL)
		{
			//SetStatus(true);
			HtmlUrl = DownHtml::GetUrlHtml(DealUrl.c_str());
			*DeptName = DownHtml::GetGateGory(HtmlUrl);
			PostThreadMessage(m_MainThrID, MSG_DEPTNAME, (WPARAM)DeptName, 0);
			SetStatus(true);
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return 0;
}


bool MyThread::IsFree()
{
	return m_IsFree;
}

void MyThread::SetStatus(bool STATUS)
{
	m_IsFree = STATUS;
}

DWORD MyThread::GetThreadID()
{
	return m_ThreadID;	
}

void MyThread::AssigTask(const std::string &TaskURL)
{
	m_MyUrl = TaskURL;
	SetStatus(false);
	//ReceiveTask
	PostThreadMessage(m_ThreadID, MSG_DEAL_URL, 0, 0);
}