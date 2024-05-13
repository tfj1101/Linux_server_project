#include<iostream>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
using namespace std;
void mycleanup(void* arg)
{
	cout << "mycleanup:" << *(int*)arg << endl;
}

void* thfunc(void* arg)
{
	int i = 1;
	cout << "thread starting------" << endl;
	pthread_cleanup_push(mycleanup, &i);
	while (true)
	{
		i++;
		cout << "i = " << i << endl;
		pthread_testcancel();
	}
	cout << "this line will not run" << endl;
	pthread_cleanup_pop(0);

	return (void*)0;
}

int main()
{
	void* ret = NULL;
	int iret = 0;
	pthread_t pid;
	pthread_create(&pid, NULL, thfunc, NULL);
	sleep(2);
	pthread_cancel(pid);
	pthread_join(pid, &ret);
	if (ret == PTHREAD_CANCELED)
	{
		cout << "thread has stopped,and exit code:" << ret << endl;
	}
	else
	{
		cout << "some error occured" << endl;
	}

	return 0;
}
