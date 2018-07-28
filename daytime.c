#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdio.h>
#include<unistd.h>
#include<assert.h>

int main(int argc,char* argv[])
{
	assert(argc == 2);
	char* host = argv[1];
	struct hostent* hostinfo = gethostbyname(host);
	assert(hostinfo != NULL);

	struct servent* servinfo = getservbyname("daytime","tcp");
	assert(servinfo != NULL);
	printf("daytime port is %d\n",ntohs(servinfo->s_port));

	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = servinfo->s_port;
	address.sin_addr = *(struct in_addr*)*hostinfo->h_addr_list;

	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	int result = connect(sockfd,(struct sockaddr*)&address,sizeof(address));
	assert(result != -1);

	char buff[128];
	result = read(sockfd,buff,128);
	assert(result > 0);
	buff[result] = 0;
	printf("the day time is: %s",buff);
	close(sockfd);

	return 0;
}
