#include<thread>
#include<mutex>
#include<iostream>

volatile int count(1);
std::mutex mtx;

void func()
{
	for (int i = 0; i < 10000; i++)
	{
		mtx.lock();
		count++;
		mtx.unlock();
	}
}

int main()
{
	std::thread threads[10];
	for (int i = 0; i < 10; i++)
	{
		threads[i] = std::thread(func);
	}
	for (auto& t : threads)
		t.join();
	std::cout << "count to " << count << ",all thread was done!" << std::endl;	
	return 0;
}