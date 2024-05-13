#pragma once
#ifndef __THREAD_POOL_H
#define __THREAD_POOL_H

#include<pthread.h>
#include<string>
#include<vector>
using namespace std;

class CTask
{
protected:
	string m_strTaskName;
	void* m_ptrData;

public:
	CTask();
	CTask(string& taskName) :m_strTaskName(taskName), m_ptrData(NULL)
	{

	}
	virtual int run() = 0;
	void setData(void* data);
	virtual ~CTask();
};

class CThreadPool
{
private:
	static vector<CTask*> m_vecTaskList;
	static bool shutdown;
	int m_iThreadNum;
	pthread_t* pthread_id;
	static pthread_mutex_t m_pthreadMutex;
	static pthread_cond_t  m_pthreadCond;

protected:
	static void* ThreadFunc(void* threadData);
	//static int MoveToldle(pthread_t* tid);
	//static int MoveToBusy(pthread_t* tid);
	int Create();

public:
	CThreadPool(int threadNum);
	int addTask(CTask* task);
	int StopAll();
	int getTaskSize();

};


#endif // !__THREAD_POOL_H

