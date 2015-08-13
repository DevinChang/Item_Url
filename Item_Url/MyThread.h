#pragma once

#include <iostream>
#include <Windows.h>
#include <process.h>
#include <string>
#define WIN32_LEAN_AND_MEAN

#define MSG_DEAL_URL 100
#define MSG_DEPTNAME 101
/*
�߳��ࣺͨ�������������һ���̣߳����������ҵ�񣬷��ظ����߳̽����
*/

typedef unsigned (WINAPI *PBIGINTHREADFUNCEX_THREADFUNC)(LPVOID lpThreadParameter);
typedef unsigned *PBINGTHREADEX_THREADID;


typedef unsigned (WINAPI *PBEGINTHREADEX_THREADFUNC) (LPVOID lpThreadParameter);
typedef unsigned *PBGINTHREADEX_THREADID;

typedef struct ThreadData
{
	std::string s_DepetName;
	std::string s_URL;
}ThreadData;

class MyThread
{
public:
	MyThread() : m_hThread(NULL), m_ThreadID(0), m_IsFree(true){}
	void StartThread(DWORD);
	void WaitForExit();
	static DWORD WINAPI ThreadFunc(LPVOID);
	bool IsFree();
	void SetStatus(bool);
	HANDLE GetHandle();
	void AssigTask(const std::string &);
	DWORD GetThreadID();
	~MyThread(){ CloseHandle(m_hThread);}
protected:
	virtual DWORD ThreadMemberFunc(const std::string &);
	std::string m_MyUrl;
	HANDLE m_hThread;
	DWORD m_ThreadID;
	DWORD m_MainThrID;
private:
	bool m_IsFree;
};

