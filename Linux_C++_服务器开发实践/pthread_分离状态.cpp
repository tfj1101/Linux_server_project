//#define _GNU_SOURCE
#include<pthread.h>
#include<stdio.h>
#include<iostream>
#include<unistd.h>
using namespace std;

void* thfun(void* arg)
{
	cout<<"thread is running"<< endl;
}

int main(int argc, char* argv[])
{
	pthread_t pid1;
	int n = 100;
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	int ret = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	if (ret != 0)
	{
		cout << "set detach failed!"<<ret << endl;
	}
	pthread_create(&pid1, &attr, thfun, NULL);
	cout << "main thread will exit" << endl;
	pthread_exit(NULL);
	cout << "main thread has exited" << endl;
	sleep(1);
	return 0;
}