//OpenMPÖ¸µ¼Óï¾ä°¸Àý
#include <omp.h>
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <time.h>

using namespace std;

int var;
#pragma omp threadprivate(var)

int main()
{
//parallel
#pragma omp parallel 
	{
		printf("Hello World! Thread ID: %d\n",omp_get_thread_num());
	}
	printf("\n");

//for
#pragma omp for
	for(int i=0;i<4;i++)
		printf("i= %d, Thread ID: %d\n",i,omp_get_thread_num());
	printf("\n");

//parallel for
#pragma omp parallel for
	for(int i=0;i<4;i++)
		printf("i= %d, Thread ID: %d\n",i,omp_get_thread_num());
	printf("\n");

//sections, section
#pragma omp sections
	{
#pragma omp section
		printf("section1, Thread ID: %d\n",omp_get_thread_num());
#pragma omp section
		printf("section2, Thread ID: %d\n",omp_get_thread_num());
#pragma omp section
		printf("section3, Thread ID: %d\n",omp_get_thread_num());
#pragma omp section
		printf("section4, Thread ID: %d\n",omp_get_thread_num());
	}
	printf("\n");

//parallel sections
#pragma omp parallel sections
	{
#pragma omp section
		printf("section1, Thread ID: %d\n",omp_get_thread_num());
#pragma omp section
		printf("section2, Thread ID: %d\n",omp_get_thread_num());
#pragma omp section
		printf("section3, Thread ID: %d\n",omp_get_thread_num());
#pragma omp section
		printf("section4, Thread ID: %d\n",omp_get_thread_num());
	}
	printf("\n");

//master
	int a[5]={0};
#pragma omp parallel
	{		
#pragma omp for
		for(int i=0;i<5;i++)
			a[i]=i*i;
//#pragma omp master
		for(int i=0;i<5;i++)
			printf("a[%d]=%d, thread ID: %d\n",i,a[i],omp_get_thread_num());
	}
	printf("\n");

//single
#pragma omp parallel
	{
#pragma omp single
		printf("single thread. thread ID: %d\n",omp_get_thread_num());
	printf("multiple threads. thread ID: %d\n",omp_get_thread_num());
	}
	printf("\n");

//atomic
	int count=0;
#pragma omp parallel
	{
		for(int i=0;i<1000000;i++)
		{
//#pragma omp atomic
			count++;
		}
	}
	printf("count=%d\n",count);
	printf("\n");

//barrier
	//Example 1
	int x,y,z;
	static SYSTEMTIME timex,timey;
#pragma omp parallel num_threads(2)
	{	
		int tid=omp_get_thread_num();
		if(tid==1)
		{
			x=2;
			GetSystemTime(&timex);
			printf("timex= %u:%u:%u\n",timex.wMinute,timex.wSecond,timex.wMilliseconds);
		}
		else
		{
			y=1;
			GetSystemTime(&timey);
			printf("timey= %u:%u:%u\n",timey.wMinute,timey.wSecond,timey.wMilliseconds);
		}
//#pragma omp barrier
		printf("z=x+y= %d, Thread ID: %d\n",
			z=x+y,omp_get_thread_num());
	}
	printf("\n");

	//Example 2
#pragma omp parallel num_threads(2)
	{
		int tid=omp_get_thread_num();
		if(tid==0)
		{
			//Sleep(2000);
			printf("Thread 0 is awake.\n");
		}
		else
		{
			//Sleep(4000);
			printf("Thread 1 is awake.\n");
		}
//#pragma omp barrier
		printf("Thread 0 and Thread 1 are awake.\n");
	}
	printf("\n");

//critical
#pragma omp parallel 
	{
//#pragma omp critical
		cout<<omp_get_thread_num()<<omp_get_thread_num();
	}
	printf("\n\n");

//threadprivate
	cout<<"Thread ID: "<<omp_get_thread_num()<<", &var: "<<&var<<endl;
#pragma omp parallel 
	{
#pragma omp critical
		cout<<"Thread ID: "<<omp_get_thread_num()<<", &var: " <<&var<<endl; 
	}
	printf("\n");

//ordered
#pragma omp parallel
	{
#pragma omp for ordered
		for(int i=0; i<8; i++)
		{
#pragma omp ordered
#pragma omp critical
			printf("i= %d, Thread ID: %d\n",i,omp_get_thread_num());
		}
	}
	printf("\n");
	return 0;
}
