Client Program:
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#define SRV_IP_ADRS  "127.0.0.1"
#define SRV_UDP_PORT 8000
#define MAX_MSG      100
void errExit(char *str)
{
    puts(str);
    exit(0);
}
int main( )
{
    int sockFd;
    struct sockaddr_in srvAdr;
    char txmsg[MAX_MSG];
    char rxmsg[MAX_MSG];
    int n;
    if((sockFd = socket (AF_INET,SOCK_DGRAM,0))< 0)
    {         errExit("can't open datagram socket \n");
    }
    memset ( &srvAdr,0,sizeof(srvAdr));
    srvAdr.sin_family = AF_INET;
    srvAdr.sin_addr.s_addr = inet_addr(SRV_IP_ADRS);
    srvAdr.sin_port = htons (SRV_UDP_PORT);
    printf("Enter message to send :\n");
    fgets(txmsg,MAX_MSG,stdin);
    n = strlen(txmsg)+1;
    if(sendto(sockFd,txmsg,n,0,(struct sockaddr *)&srvAdr,sizeof(srvAdr ))!=n)
    {         errExit("sendto error \n");
    }
    n = recv(sockFd,rxmsg,MAX_MSG,0);
    printf("n=%d\n",n);
    if(n < 0)
    {         errExit("recv error \n");
    }
    printf("Time Received from the server :%s\n",rxmsg);
}
