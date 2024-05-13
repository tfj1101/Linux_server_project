#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int i = 0;

void* thread1(void* arg)
{
	for (i = 1; i <= 20; i++)
	{
		pthread_mutex_lock(&mutex);
		if (i % 3 == 0)
		{
			pthread_cond_signal(&cond);
		}
		else
		{
			printf("thread1:%d\n", i);
		}
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
}

void* thread2(void* arg)
{
	while (i<20)
	{
		pthread_mutex_lock(&mutex);
		if (i%3!=0)
		{
			pthread_cond_wait(&cond, &mutex);
		}
		printf("--------------thread2: %d\n", i);
		pthread_mutex_unlock(&mutex);
		sleep(1);
		i++;
	}
}

int main(void)
{
	pthread_t pid1;
	pthread_t pid2;
	pthread_create(&pid1, NULL, thread2, NULL);
	pthread_create(&pid2, NULL, thread1, NULL);

	pthread_join(pid2,NULL);
	return 0;
}