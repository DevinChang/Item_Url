#include "threadpool.h"
#include "util.h"


void CThreadPool::CreateThreadPool(int thread_count)
{
	for (int i = 0; i < thread_count; i++)
	{
		boost::shared_ptr<CThread> managed_thread(new CThread);
		managed_thread->StartThread();
		vec_thread_.push_back(managed_thread);
	}
}

int CThreadPool::GetFreeThreadIndex()
{
	for (unsigned int i = 0; i < vec_thread_.size(); i++)
	{
		if (vec_thread_[i]->IsFree())
			return i;
	}
	return -1;
}



int CThreadPool::GetFreeThreadCount()
{
	int free_count = 0;
	for (unsigned int i = 0; i < vec_thread_.size(); i++)
	{
		if (vec_thread_[i]->IsFree())
			free_count++;
	}
	return free_count;
}

void CThreadPool::ReceiveTask(NodeUrl node_url)
{
	int index = GetFreeThreadIndex();
	if (index == -1)
		return ;
	vec_thread_[index]->AssigTask(node_url);
}

void CThreadPool::ReceiveTask(const std::string &target_url)
{
	int index = GetFreeThreadIndex();
	if (index == -1)
		return ;
	vec_thread_[index]->AssigTask(target_url);
}

CThreadPool::~CThreadPool()
{
	for (unsigned int i = 0; i < vec_thread_.size(); i++)
		vec_thread_[i]->Destroy();
}