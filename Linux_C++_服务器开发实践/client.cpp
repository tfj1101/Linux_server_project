// client.c 客户端
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>
#define SERVPORT 3333
#define MAXDATASIZE 100
int random_number()//generating a random number
{
    int a;
    srand((unsigned)time(NULL));
    a = rand();
    return a;
}
int main(int argc, char* argv[])
{
    int sockfd, recvbytes;
    int value = 0;
    char buf[MAXDATASIZE];
    struct hostent* host;
    struct sockaddr_in serv_addr;
    if (argc < 2)
    {
        fprintf(stderr, "Please enter the server's hostname!\n");
        exit(1);
    }
    if ((host = gethostbyname(argv[1])) == NULL)
    {
        herror("gethostbyname error！");
        exit(1);
    }
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)//建立socket --
    {
        perror("socket create error！");
        exit(1);
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERVPORT);
    serv_addr.sin_addr = *((struct in_addr*)host->h_addr);
    bzero(&(serv_addr.sin_zero), 8);
    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(struct sockaddr)) == -1) //请求连接 --
    {
        perror("connect error！");
        exit(1);
    }
    //successful connection
    if ((recvbytes = recv(sockfd, buf, MAXDATASIZE, 0)) == -1)//接收数据 --
    {
        perror("connect 出错！");
        exit(1);
    }
    buf[recvbytes] = '\0';
    printf("收到: %s", buf);
    //send pieces of message to server
    while (1)
    {
        //generating a random number and sending it to the host
        value = random_number();
        sprintf(buf, "%d", value);//int to string
        send(sockfd, buf, (int)strlen(buf), 0);
        //every one second client sends a random number converted to string to host
        sleep(1);
    }
    close(sockfd);//关闭连接 --
}
