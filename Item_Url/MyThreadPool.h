#pragma once
#include "MyThread.h"
#include <vector>

#define THREAD_POOL_SIZE 10
#define MSG_DEAL_URL 100
/*
�����̳߳�ֻ���߳̽��в�����������ҵ��
�������������
��������߳�����̳߳ء�
���ÿ���̵߳�״̬����⵽�����̣߳����ظ������̡�
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

