- **(a)Implementation of iterative echo server using connection oriented socket system calls**
    - Server:
        
        ```c
        // Creating an echo server using TCP [connection Oriented]:

        #include<stdio.h>
        #include<stdlib.h>
        #include<unistd.h>
        #include<sys/socket.h>
        #include<sys/types.h>
        #include<netinet/in.h>
        #include<string.h>
        #include<arpa/inet.h>

        #define ERROR -1
        // Maximum clients that can connect with each other
        #define MAX_CLIENTS 2
        #define PORT 5556
        // Max Data that can be transfered b/w the server and the client.
        #define MAX_DATA 1024

        int main(){
            struct sockaddr_in serverAddress ,clientAddress;
            int sock, newClient;
            int sockaddr_len= sizeof(struct sockaddr_in);
            int data_len;
            char data[MAX_DATA];

            // creating a socket
            sock = socket(AF_INET,SOCK_STREAM,0);
            // sock = -1;
            if(sock<0){
                perror("[-] Can't open socket stream \n");
                exit(-1);
            }
            else{
                printf("[+] Socket opened\n");
            }
            serverAddress.sin_family=AF_INET;
            serverAddress.sin_port=htons(PORT);
            serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
            bzero(&serverAddress.sin_zero,8);
            // Binding
            int Binding = bind(sock,(struct sockaddr *)&serverAddress,sockaddr_len);
            if(Binding<0){
                perror("[-] Can't Bind the socket with socket Address\n");
                exit(-1);
            }
            printf("[+] Socket Address Assigned to the server\n");
            //Listening
            if((listen(sock,MAX_CLIENTS))<0){
                perror("[-] Server not Listening\n");
                exit(-1);
            }
            printf("[+] Socket is Listening\n");
            while(1){
                newClient = accept(sock,(struct sockaddr *)&clientAddress,&sockaddr_len);
                // Accept
                if(newClient==ERROR){
                    perror("[-] connection not Accepted\n");
                    exit(-1);
                }
                printf("[+] connection Accepted\n");
                printf("New Client Connected\nPort No: %d\nIp: %s\n",ntohs(clientAddress.sin_port),inet_ntoa(clientAddress.sin_addr));
                data_len =1;
                while(data_len){
                    data_len= recv(newClient,data,MAX_DATA,0);
                    if(data_len){
                        send(newClient,data,data_len,0);
                        data[data_len] = '\0';
                        printf("Sent Message : %s\n",data);
                    }
                }
                printf("Client Disconnected \n");
                close(newClient);
            }
            close(sock);
            return 0;
        }
        ```
        
    - Client:
        
        ```c
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
        #define PORT 5556
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
        ```
