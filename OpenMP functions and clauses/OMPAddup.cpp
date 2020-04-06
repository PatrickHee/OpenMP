//分别通过单线程，人工多线程，OMP多线程计算0-10000000的累加和
#include <omp.h>
#include <iostream>
#include <time.h>
#include <Windows.h>

#define N 10000000

using namespace std;

clock_t start,stop;
long long int funcsum[4]={0};

//函数声明
long long int SingleThread(int n);

DWORD WINAPI Threadfunc1(PVOID pM)
{
	for(int i=1;i<=2500000;i++)
		funcsum[0]+=i;
	return 0;
}

DWORD WINAPI Threadfunc2(PVOID pM)
{
	for(int i=2500001;i<=5000000;i++)
		funcsum[1]+=i;
	return 0;
}

DWORD WINAPI Threadfunc3(PVOID pM)
{
	for(int i=5000001;i<=7500000;i++)
		funcsum[2]+=i;
	return 0;
}

DWORD WINAPI Threadfunc4(PVOID pM)
{
	for(int i=7500001;i<=10000000;i++)
		funcsum[3]+=i;
	return 0;
}

int main()
{
	long long int sum;
	//单线程计算
	sum=0;
	start=clock();
	sum=SingleThread(N);
	stop=clock();
	cout<<"Single thread result is "<<sum<<", execute time: "<<
		(double)(stop-start)*1000/CLOCKS_PER_SEC<<
		"ms"<<endl;

	//人工四线程计算
	sum=0;
	start=clock();
	HANDLE hThread[4];
    hThread[0]=CreateThread(NULL,NULL,Threadfunc1,NULL,0,NULL);
    hThread[1]=CreateThread(NULL,NULL,Threadfunc2,NULL,0,NULL);
    hThread[2]=CreateThread(NULL,NULL,Threadfunc3,NULL,0,NULL);
    hThread[3]=CreateThread(NULL,NULL,Threadfunc4,NULL,0,NULL);
    WaitForMultipleObjects(4,hThread,TRUE,INFINITE);
	for(int i=0;i<4;i++)
		sum+=funcsum[i];
	stop=clock();
	cout<<"Four thread functions result is "<<sum<<", execute time: "<<
		(double)(stop-start)*1000/CLOCKS_PER_SEC<<
		"ms"<<endl;

	//OMP多线程计算
	sum=0;
	start=clock();
#pragma omp parallel for reduction(+:sum)//归约，避免数据竞争
	for(int i=1;i<=N;i++)
		sum+=i;
	stop=clock();
	cout<<"OMP Multi-threads result is "<<sum<<", execute time: "<<
		(double)(stop-start)*1000/CLOCKS_PER_SEC<<
		"ms"<<endl;

	//不用规约的错误案例
	printf("Wrong Example:\n");
#pragma omp parallel for
	for(int i=1;i<=N;i++)
		sum+=i;
	stop=clock();
	cout<<"OMP Multi-threads result is "<<sum<<", execute time: "<<
		(double)(stop-start)*1000/CLOCKS_PER_SEC<<
		"ms"<<endl;
	return 0;
}

//函数定义
long long int SingleThread(int n)
{
	long long int sum=0;
	for(int i=1;i<=N;i++)
		sum+=i;
	return sum;
}
