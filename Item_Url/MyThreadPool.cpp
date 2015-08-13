#include "MyThreadPool.h"


void MyThreadPool::CreateThreadPool(DWORD MainThrID)
{
	for (int i = 0; i < THREAD_POOL_SIZE; i++)
	{
		MyThread *NewThr = new MyThread;
		NewThr->StartThread(MainThrID);
		m_VecThr.push_back(NewThr);
	}
}

//
int MyThreadPool::GetFreeThreadIndex()
{

	for (int i = 0; i < m_VecThr.size(); i++)
	{
		if (m_VecThr[i]->IsFree())
		{
			return i;
		}
	}
	return -1;
}



int MyThreadPool::GetFreeThreadCount()
{
	int FreeCount = 0;
	for (int i = 0; i < m_VecThr.size(); i++)
	{
		if (m_VecThr[i]->IsFree())
		{
			FreeCount++;
		}
	}
	return FreeCount;
}

void MyThreadPool::ReceiveTask(std::string &TaskURL)
{
	TargetURL = TaskURL;
	int Index = GetFreeThreadIndex();
	if (Index == -1)
	{
		return ;
	}
	
	m_VecThr[Index]->AssigTask(TaskURL);
}