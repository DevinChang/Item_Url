#pragma once
#include <vector>
#include "boost/smart_ptr.hpp"
#include "thread.h"



/*
�����̳߳�ֻ���߳̽��в�����������ҵ��
�������������
��������߳�����̳߳ء�
���ÿ���̵߳�״̬����⵽�����̣߳����ظ������̡�
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

