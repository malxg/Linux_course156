#include "net.h"

int main(int argc,char *argv[])
{
	int sockfd,recvbytes;
	char buf[MAXDATASIZE];
	struct hostent *host;
	struct sockaddr_in serv_addr;
	
	if(argc<2)
	{
		fprintf(stderr,"error!\n");
		exit(1);
	}
	if((host=gethostbyname(argv[1]))==NULL)
	{
		perror("gethostbyname error!\n");
		exit(1);
	}
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		perror("socket failed!");
		exit(1);
	}
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(SERVPORT);
	serv_addr.sin_addr=*((struct in_addr *)host->h_addr);
	bzero(&(serv_addr.sin_zero),8);
	if(connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(struct sockaddr))==-1)
	{
		perror("connect failed!");
		exit(1);
	}
	if((recvbytes=recv(sockfd,buf,MAXDATASIZE,0))==-1)
	{
		perror("receive failed!");
		exit(1);
	}
	buf[recvbytes]='\0';
	printf("receive:%s",buf);	
	send(sockfd,"wenjiajun",9,0);
	close(sockfd);	
}
