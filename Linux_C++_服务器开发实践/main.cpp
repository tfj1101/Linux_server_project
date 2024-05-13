#include<cstdio>
#include<stdlib.h>
#include<unistd.h>
#include"thread_pool.h"

class MyTask :public CTask
{
public:
	MyTask()
	{

	}

	int run()
	{
		printf("%s \n", (char*)m_ptrData);
		int x = rand() % 4 + 1;
		sleep(x);
		return 0;
	}
	~MyTask(){}
};

int main()
{
	MyTask taskobj;
	char szTemp[] = { "hello!" };
	taskobj.setData((void*)szTemp);
	CThreadPool threadpool(5);
	for (int i = 0; i < 10; i++)
	{
		threadpool.addTask(&taskobj);
	}
	while (true)
	{
		printf("There arre still %d tasks need to handle\n", threadpool.getTaskSize());
		if (threadpool.getTaskSize() == 0)
		{
			//Çå³ýÏß³Ì³Ø
			if (threadpool.StopAll() == -1)
			{
				printf("Thread pool clear,exit.\n");
				exit(0);
			}
			
		}
		sleep(2);
		printf("2 seconds later...\n");
	}
	return 0;
}