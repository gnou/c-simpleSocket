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
    int sockfd, n;
    char recvline[MAXLINE], sendline[MAXLINE];
    struct sockaddr_in serverAddr;

    if(argc != 2){
        printf("usage: ./client <ipaddress>\n");
    }

    //create socket fd
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("socket creation failed");
    }

    //clean serverAddr
    memset(&serverAddr, 0, sizeof(serverAddr));
    //file serverAddr
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(4444);
    if( inet_pton(AF_INET, argv[1], &serverAddr.sin_addr) < 0){
        printf("ip address presientation to numeric failed");
        exit(0);
    }

    //connect
    if( connect(sockfd, (struct sockadd*)&serverAddr, sizeof(serverAddr)) < 0){
        printf("connect to server failed");
        exit(0);
    }

    printf("send msg to server: \n");
    fgets(sendline, MAXLINE, stdin);
    //send
    if( send(sockfd, sendline, strlen(sendline), 0) < 0){
        printf("send error");
        exit(0);
    }

    //close
    close(sockfd);
    exit(1);
}
