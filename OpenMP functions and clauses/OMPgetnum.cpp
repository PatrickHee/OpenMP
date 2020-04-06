//利用OpenMP获取计算机核心数量与线程数量
#include <omp.h>
#include <iostream>
#include <stdio.h>
#include <Windows.h>

CRITICAL_SECTION cs;

using namespace std;

int main()
{

	//串行执行开始
	cout<<"Serial begin."<<endl;
	cout<<"Processor number: "<<omp_get_num_procs()<<endl;//获取逻辑处理器个数
	cout<<"Thread number: "<<omp_get_num_threads()<<endl;//获取线程数量
	cout<<"Parallel begin."<<endl;//并行执行开始
	InitializeCriticalSection(&cs);
	omp_set_num_threads(16);
#pragma omp parallel num_threads(12)
	{
		EnterCriticalSection(&cs);
		cout<<"Processor number: "<<omp_get_num_procs()<<
			" Thread number: "<<omp_get_num_threads()<<
			" Thread ID: "<<omp_get_thread_num()<<endl;
		LeaveCriticalSection(&cs);
	}
	cout<<"Parallel end."<<endl;//并行执行结束
	cout<<"Serial end."<<endl;//串行执行结束

	
	/*
	//串行执行开始
	printf("Serial begin.");
	printf("\nProcessor number: %d",omp_get_num_procs());//获取逻辑处理器个数
	printf("\nThread number: %d",omp_get_num_threads());//获取线程数量
	printf("\nParallel begin.");//并行执行开始
	//omp_set_num_threads(4);
#pragma omp parallel 
	{
		printf("\nProcessor number: %d, Thread number: %d, Thread ID: %d"
			,omp_get_num_procs(),omp_get_num_threads(),omp_get_thread_num());
	}
	printf("\nParallel end.");//并行执行结束
	printf("\nSerial end.\n");//串行执行结束
	*/
	return 0;
}
