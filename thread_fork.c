/********************************************************************************************************
 *																										*
 *	2018-8-7																							*
 *	Zhaoruiqi																							*
 *	多线程中使用fork，子进程只拥有一个执行线程即调用fork的线程的复制。同时，子进程将继承夫进程锁的状态	*
 *	这就引发了一个问题，子进程不清楚从父进程中继承而来的互斥锁处于什么状态。							*
 *																										*
 ********************************************************************************************************/

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <wait.h>

pthread_mutex_t mutex;

void* another(void* arg)
{
	printf("in child thread,lock the mutex\n");
	pthread_mutex_lock(&mutex);
	sleep(5);
	pthread_mutex_unlock(&mutex);
}

int main()
{
	pthread_mutex_init(&mutex,NULL);
	pthread_t id;
	pthread_create(&id,NULL,another,NULL);

	sleep(1);//父进程的主线程暂停1s，以确保执行fork操作之前，子线程已经开始运行并且获得了互斥变量mutex
	pid_t pid = fork();
	if(pid < 0)
	{
		pthread_join(id,NULL);
		pthread_mutex_destroy(&mutex);
		return 1;
	}
	else if(pid == 0)
	{
		printf("I am in the child,want to get the lock\n");
		pthread_mutex_lock(&mutex);
		printf("I can not run to here,...\n");
		pthread_mutex_unlock(&mutex);
		exit(0);
	}
	else
	  wait(NULL);

	pthread_join(id,NULL);
	pthread_mutex_destroy(&mutex);
	return 0;
}
