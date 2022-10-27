//3.Implementation of Iterative Daytime server using //connectionless service(UDP).
//Server Program:
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
void errExit(char *str)
{
    puts(str);
    exit(0);
}
int main()
{
   unsigned long t;
   char *st,buffer[512],MAX_MSG;
   int n,i,l,ml,sockfd,newsockfd,cliLen;
   struct sockaddr_in serv_addr,cli_addr;
   sockfd=socket(AF_INET,SOCK_DGRAM,0);
   serv_addr.sin_family=AF_INET;
   serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
   serv_addr.sin_port=htons(8000);
   bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
   l=sizeof(cli_addr);
        cliLen = sizeof(cli_addr);
        n = recvfrom(sockfd,buffer,MAX_MSG,0 ,(struct sockaddr*)&cli_addr,&cliLen);
        if(n < 0)
        {
            errExit("recvfrom error \n");
        }
    printf("\nMessage received from client: %s", buffer);
      t=time(&t);
      st=(char *)ctime(&t);
      strcpy(buffer,st);
     n=sizeof(buffer);
     if(sendto(sockfd,buffer, n,0,(struct sockaddr *)&cli_addr,cliLen) !=n)
        {
                errExit("sendto error \n");
        }
        printf ("Time sent…");
   }
