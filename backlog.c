/*
 *int listen(int sockfd,int backlog);
 *sockfd参数指定被监听的socket。backlog参数提示内核监听队列的最大长度。监听队列的长度如果超过backlog，服务器将不
 *受理新的客户连接，客户端也将收到ECONNERFUSED错误信息。在内核版本2.2之前的Linux中，backlog参数是指定所有处于半
 *连接状态（SYN_RCVD）和完全连接（ESTABLISHED）的socket的上限。自内核2.2以后，它只表示处于完全连接状态的socket上
 *此代码测试blacklog的参数意义，具体做法是服务器只调用listen不accept，然后用客户端大量连接服务器。用netstat查看
 *连接状态
 *
 *设定backlog的值位5，启动bash telnet连接服务器，每连接一次用netstat -nat | grep port查看来年接状态
 *经过测试，服务器接受6个连接为完全连接状态，第七个处于SYN_RECV.
 *
 *
 *										 */



#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

static int stop = 0;
//SIGTERM信号处理函数，触发时结束主程序中的循环
static void handle_term(int sig)
{
	stop = 1;
}

int main(int argc,char* argv[])
{
	signal(SIGTERM,handle_term);

	if(argc <= 3)
	{
		printf("usage: %s ip_address port_number backlog\n");
		return 1;
	}
	const char* ip = argv[1];
	short port = atoi(argv[2]);
	int backlog = atoi(argv[3]);

	int sock = socket(PF_INET,SOCK_STREAM,0);
	assert(sock >= 0);

	struct sockaddr_in address;
	bzero(&address,sizeof(address));
	address.sin_family = AF_INET;
	inet_pton(AF_INET,ip,&address.sin_addr);
	address.sin_port = htons(port);

	int ret = bind(sock,(struct sockaddr*)&address,sizeof(address));
	assert(ret != -1);

	ret = listen(sock,backlog);
	assert(ret != -1);

	while(!stop)
	  sleep(1);

	close(sock);
	return 0;
}
