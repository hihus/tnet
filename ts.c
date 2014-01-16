#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


int main(int argc , char * argv[]){
	if(argc <2){
		printf("the params is less than two, you at least intput the [1] host and [2] port! \n");
		return 1;
	}
	const char * ip = argv[1];
	int port = atoi(argv[2]);
	struct sockaddr_in address;
	bzero(&address,sizeof(address));
	address.sin_family = AF_INET;
	inet_pton(AF_INET,ip,&address.sin_addr);
	address.sin_port = htons(port);
	int sock = socket(PF_INET,SOCK_STREAM,0);
	assert(sock >= 0);
	int ret = bind(sock,(struct sockaddr*)&address,sizeof(address));
	assert(ret != -1);
	ret = listen(sock,10);
	assert(ret != -1);

	struct sockaddr_in client;
	socklen_t cs_len = sizeof(client);
	int conn = accept(sock,(struct sockaddr_in * )&client,&cs_len);
	if(conn <0){
		printf("accept error from %s \n",ip);
	}else{
		int i = 0;
		char * buff[512];
		int re = 0;
		while(1){
			re = recv(conn,buff,sizeof(buff),0);
			if(re > 0){
				printf("recv : %s \n",buff);
			}else{
				continue;
			}
			i++;
			if(i>10){
				break;
			}
		}
	}

	close(conn);
	close(sock);
	return 0;
}