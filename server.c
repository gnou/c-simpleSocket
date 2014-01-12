#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAXLINE 4096

int main(int argc, char** argv)
{
    int listenfd, connfd;
    struct sockaddr_in servAddr;
    char buff[MAXLINE];
    int n;

    //create socket fd
    if( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("socket creation failed");
        exit(0);
    }

    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(4444);

    //bind
    if( bind(listenfd, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0){
        printf("bind error\n");
        exit(0);
    }

    //listen
    if( listen(listenfd, 10) < 0){
        printf("listen error\n");
        exit(0);
    }

    printf("=====wait for client's request=====\n");

    //accept
    while(1){
        if((connfd = accept(listenfd, (struct sockaddr*)NULL, NULL)) < 0){
            printf("accept error\n");
            continue;
        }

        n = recv(connfd, buff, MAXLINE, 0);
        buff[n] = '\0';
        printf("receive msg from client: %s\n", buff);
        close(connfd);
    }

    close(listenfd);
    exit(1);
}
