#include<pthread.h>
#include<iostream>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<limits.h>

static void* thread_start(void* arg)
{
	int i, res;
	size_t stack_size;
	pthread_attr_t gattr;
	res = pthread_getattr_np(pthread_self(), &gattr);
	res = pthread_attr_getstacksize(&gattr, &stack_size);
	pthread_attr_destroy(&gattr);
	std::cout << "default stack size is " << stack_size << " byte; minmum is " << PTHREAD_STACK_MIN << std::endl;
}

int main(int argc, char* argv[])
{
	pthread_t pid;
	int s;
	s = pthread_create(&pid, NULL, &thread_start, NULL);
	pthread_join(pid, NULL);

}