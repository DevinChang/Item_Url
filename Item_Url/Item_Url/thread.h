#pragma once

#include <iostream>
#include <Windows.h>
#include <process.h>
#include <string>

#define WIN32_LEAN_AND_MEAN


/*
线程类：通过这个类来创建一个线程，并处理相关业务，返回给主线程结果。
*/

typedef unsigned (WINAPI *PBIGINTHREADFUNCEX_THREADFUNC)(LPVOID lpThreadParameter);
typedef unsigned *PBINGTHREADEX_THREADID;


typedef unsigned (WINAPI *PBEGINTHREADEX_THREADFUNC) (LPVOID lpThreadParameter);
typedef unsigned *PBGINTHREADEX_THREADID;

typedef struct ThreadData
{
	std::string department;
	std::string dept_url;
	bool deal;
}ThreadData;

struct NodeUrl
{
	std::string deal_url;
	bool isdeal;
};

class CThread
{
public:
	CThread() : thread_(NULL), thread_id_(0), isfree_(true){}
	~CThread();
	void StartThread();
	static DWORD WINAPI ThreadFunc(LPVOID);
	bool IsFree();
	void SetStatus(bool);
	HANDLE GetHandle();
	void AssigTask(NodeUrl);
	void AssigTask(const std::string &);
	DWORD GetThreadID();
	void Destroy();
private:
	HANDLE thread_;
	DWORD thread_id_;
	DWORD main_thread_id_;
	bool isfree_;
	NodeUrl node_url_;
	std::string tar_url_;
};

