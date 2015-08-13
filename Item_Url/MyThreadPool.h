#pragma once
#include "MyThread.h"
#include <vector>

#define THREAD_POOL_SIZE 10
#define MSG_DEAL_URL 100
/*
创建线程池只对线程进行操作，不处理业务。
具体操作包括：
创建多个线程组成线程池。
检查每个线程的状态，检测到空闲线程，返回给主流程。
*/

class MyThreadPool
{
public:
	MyThreadPool() : m_WorkThreadNum(0), m_VecThr(NULL){}
	void CreateThreadPool(DWORD);
	int GetFreeThreadIndex();
	
	int GetFreeThreadCount();
	void ReceiveTask(std::string &);
protected:
	std::vector<MyThread *> m_VecThr;
private:
	int m_WorkThreadNum;
	std::string TargetURL;
};

