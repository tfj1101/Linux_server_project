// server.c 服务端
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include<netinet/in.h>
#include <sys/wait.h>
#include <arpa/inet.h> 
#define SERVPORT 3333
#define BACKLOG 10
int main()
{
    int sockfd, client_fd;
    int recvbytes;
    int sin_size;
    char buf[50];
    struct sockaddr_in my_addr;
    struct sockaddr_in remote_addr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);//建立socket --
    my_addr.sin_family = AF_INET;//AF_INET地址族
    my_addr.sin_port = htons(SERVPORT);//设定端口号(host -> networks)
    my_addr.sin_addr.s_addr = inet_addr("192.168.200.130");//32位IPv4地址
    bzero(&(my_addr.sin_zero), 8); //置前8个字节为0
    char on = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    if (bind(sockfd, (struct sockaddr*)&my_addr, sizeof(struct sockaddr)) == -1)
    {
        perror("bind 出错！");
        exit(1);
    }
    
    if (listen(sockfd, BACKLOG) == -1) //监听socket连接，设置队列中最多拥有连接个数为10  --
    {
        perror("listen 出错！");
        exit(1);
    }
    while (1)
    {
        sin_size = sizeof(struct sockaddr_in);//记录sockaddr_in结构体所占字节数
        if ((client_fd = accept(sockfd, (struct sockaddr*)&remote_addr, (socklen_t*) & sin_size)) == -1) //accept()缺省是阻塞函数，阻塞到有连接请求为止 --
        {
            perror("accept error");
            continue;
        }
        printf("收到一个连接来自： %s\n", inet_ntoa(remote_addr.sin_addr));
        if (!fork())
        {
            if (send(client_fd, "连接上了 \n", 26, 0) == -1) //--		
                perror("send 出错！");
            //receive pieces of message from host
            while (1)
            {
                recvbytes = recv(client_fd, buf, 50, 0);
                buf[recvbytes] = '\0';
                if (recvbytes == 0)//indicating that the client has been off
                {
                    printf("connection to %s closed.\n", inet_ntoa(remote_addr.sin_addr));
                    break;
                }
                printf("%s\n", buf);
                sleep(1);
            }

            close(client_fd);
            exit(0);
        }
        close(client_fd);
    }
}
