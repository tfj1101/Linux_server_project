#include<thread>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<chrono>
using namespace std;

void thfunc(int n)
{
	cout << "n = " << n << endl;
}
void thfunc1(char* c)
{
	cout << "thfunc:" << c << endl;
}
void test01()
{
	thread threads[5];
	cout << "created 5 threads" << endl;
	for (int i = 0; i < 5; i++)
	{
		threads[i] = thread(thfunc, i + 1);
	}
	for (auto& t : threads)
		t.join();
	cout << "all threads joined" << endl;
}

void test02()
{
	char s[] = { "boy and girl" };
	thread t(thfunc1, s);
	t.join();

}

struct mymsg
{
	int n;
	const char* c;
};

void thfunc2(mymsg* m)
{
	cout << "n = " << m->n << endl;
	cout << "c = " << m->c << endl; 
}
void test03()
{
	mymsg my = { 10,"zhangsan" };
	thread t(thfunc2, &my);
	t.join();
}
void test04()
{
	char s[] = { "boy and girl" };
	thread t(thfunc1, s);
	t.detach();
	cout << "before" << endl;
	pthread_exit(NULL);
	cout << "main thread this line will not run" << endl;
}

void fun(int& n)
{
	cout << "fun:" << n << endl;
	n += 20;
	this_thread::sleep_for(chrono::milliseconds(10));
}

void test05()
{
	int n = 0;
	cout << "n = " << n << endl;
	n = 10;
	thread t1(fun, ref(n));
	thread t2(move(t1));
	t2.join();
	cout << "n = " << n << endl;

}

thread::id main_id = this_thread::get_id();
void is_main_thread()
{
	if (main_id == this_thread::get_id())
	{
		cout << "this is the main thread" << endl;
	}
	else
	{
		cout << "this is not the main thread" << endl;
	}

}

void test06()
{
	is_main_thread();
	thread t(is_main_thread);
	if (t.get_id() == main_id)
	{
		cout <<"thread id = " << t.get_id() << endl;
	}
	else
	{
		cout <<"main id = " << main_id << endl;
	}
	t.join();
}

int main()
{
	//test02();
	//test03();
	//test04();
	//test05();
	test06();



}