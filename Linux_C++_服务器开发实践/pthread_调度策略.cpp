#include<pthread.h>
#include<unistd.h>
#include<iostream>
#include<sched.h>
using namespace std;
int main()
{
	cout << "Valid priority range for SCHED_OUTER: " << sched_get_priority_min(SCHED_OTHER) << "--" << sched_get_priority_max(SCHED_OTHER) << endl;
	cout << "Valid priority range for SCHED_FIFO: " << sched_get_priority_min(SCHED_FIFO) << "--" << sched_get_priority_max(SCHED_FIFO) << endl;
	cout << "Valid priority range for SCHED_RR: " << sched_get_priority_min(SCHED_RR) << "--" << sched_get_priority_max(SCHED_RR) << endl;

}