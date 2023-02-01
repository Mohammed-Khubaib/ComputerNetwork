// Client Program :
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define IP_ADRS "127.0.0.1"
#define PORT 6666
#define MAX_MSG 100

int main(){
    int sock,n;
    struct sockaddr_in serverAddress;
     char txmsg[MAX_MSG];
    char rxmsg[MAX_MSG];
    sock = socket(AF_INET,SOCK_STREAM,0);
    if(sock<0){
        perror("[-]Socket not Opened\n");
        exit(-1);
    }
    printf("[+] Socket Opened\n");
    memset(&serverAddress,0,sizeof(serverAddress));
    serverAddress.sin_family=AF_INET;
    serverAddress.sin_port=htons(PORT);
    serverAddress.sin_addr.s_addr=inet_addr(IP_ADRS);
    if(connect(sock,(struct sockaddr *)&serverAddress,sizeof(serverAddress))<0){
        perror("[-] connection failed\n");
        exit(-1);
    }
    printf("[+] connection successful\n");
    while (1)
    {
         printf("Enter message to send ,Enter # to exit :\n");
          fgets(txmsg, MAX_MSG, stdin);
            if (txmsg[0] == '#')
            {
                break;
            }
            n = strlen(txmsg) + 1;
        if (send(sock, txmsg, n, 0) != n)
        {
            perror("send error \n");
            exit(-1);
        }
        n = recv(sock, rxmsg, MAX_MSG, 0);
        if (n < 0)
        {
            perror("recv error \n");
            exit(-1);
        }
        printf("Received following message :\n%s\n", rxmsg);
    }
    

    return 0;
}