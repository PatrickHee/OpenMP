//����OpenMP��ȡ����������������߳�����
#include <omp.h>
#include <iostream>
#include <stdio.h>
#include <Windows.h>

CRITICAL_SECTION cs;

using namespace std;

int main()
{

	//����ִ�п�ʼ
	cout<<"Serial begin."<<endl;
	cout<<"Processor number: "<<omp_get_num_procs()<<endl;//��ȡ�߼�����������
	cout<<"Thread number: "<<omp_get_num_threads()<<endl;//��ȡ�߳�����
	cout<<"Parallel begin."<<endl;//����ִ�п�ʼ
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
	cout<<"Parallel end."<<endl;//����ִ�н���
	cout<<"Serial end."<<endl;//����ִ�н���

	
	/*
	//����ִ�п�ʼ
	printf("Serial begin.");
	printf("\nProcessor number: %d",omp_get_num_procs());//��ȡ�߼�����������
	printf("\nThread number: %d",omp_get_num_threads());//��ȡ�߳�����
	printf("\nParallel begin.");//����ִ�п�ʼ
	//omp_set_num_threads(4);
#pragma omp parallel 
	{
		printf("\nProcessor number: %d, Thread number: %d, Thread ID: %d"
			,omp_get_num_procs(),omp_get_num_threads(),omp_get_thread_num());
	}
	printf("\nParallel end.");//����ִ�н���
	printf("\nSerial end.\n");//����ִ�н���
	*/
	return 0;
}