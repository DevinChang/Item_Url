#pragma once
#include <vector>
#include "boost/smart_ptr.hpp"
#include "thread.h"



/*
创建线程池只对线程进行操作，不处理业务。
具体操作包括：
创建多个线程组成线程池。
检查每个线程的状态，检测到空闲线程，返回给主流程。
*/

class CThreadPool
{
public:
	CThreadPool() : busythread_count_(0), vec_thread_(NULL){}
	~CThreadPool();
	void CreateThreadPool(int);
	int GetFreeThreadIndex();
	int GetFreeThreadCount();
	void ReceiveTask(NodeUrl);
	void ReceiveTask(const std::string &);
private:
	std::vector<boost::shared_ptr<CThread>> vec_thread_;
	int busythread_count_;
};

