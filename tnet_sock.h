#ifndef TNET_SOCK
#define TNET_SOCK

#define PORT 8090
#define SERVER_ADDR 127.0.0.1

//拨号程序，失败返回0，成功返回sock fd
int tnet_dial(char * addr,int port);
int tnet_server_init(int port);
void tnet_server_poll(int listenFd);



#endif TNET_SOCK