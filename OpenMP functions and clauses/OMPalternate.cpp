//Ïß³Ì½»Ìæ
#include <iostream>
#include <omp.h>
#include <stdio.h>
#include <Windows.h>

#define N 20

using namespace std;

int main()
{
	int sum=0;
#pragma omp parallel for schedule(dynamic) num_threads(4)
	for(int i=1;i<=N;i++)
	{
		sum+=i;
		printf("i= %d, Thread ID= %d\n",i,omp_get_thread_num());
		Sleep(500);
	}
	printf("Sum= %d\n",sum);
	printf("\n");
	sum=0;
#pragma omp parallel for num_threads(4)
	for(int i=1;i<=N;i++)
	{
		sum+=i;
		printf("i= %d, Thread ID= %d\n",i,omp_get_thread_num());
		Sleep(500);
	}
	printf("Sum= %d\n",sum);
	printf("\n");
	return 0;
}
