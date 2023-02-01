- **(a)Implementation of concurrent echo server using connection oriented socket system calls**
    - Server:
        
        ```c
        #include <stdio.h>
        #include <stdlib.h>
        #include <unistd.h>
        #include <string.h>
        #include <sys/types.h>
        #include <sys/socket.h>
        #include <netinet/in.h>
        #include <arpa/inet.h>

        #define PORT 6666
        #define MAX_MSG 100

        int main()
        {
            int sock, newSock, pid, n;
            struct sockaddr_in serverAddress, clientAddress;
            int sock_len = sizeof(struct sockaddr_in);
            char data[MAX_MSG];

            sock = socket(AF_INET, SOCK_STREAM, 0);
            if (sock < 0)
            {
                perror("[-] socket not created\n");
                exit(-1);
            }
            printf("[+] Socket Created\n");
            memset(&serverAddress, 0, sock_len);
            serverAddress.sin_family = AF_INET;
            serverAddress.sin_port = htons(PORT);
            serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);

            if ((bind(sock, (struct sockaddr *)&serverAddress, sock_len)) < 0)
            {
                perror("[-]Binding Failed\n");
            }
            printf("[+] Bining Successful\n");

            if (listen(sock, 3))
            {
                perror("[-] not listening");
                exit(-1);
            }
            printf("[+] Listening\n");

            while (1)
            {
                newSock = accept(sock, (struct sockaddr *)&clientAddress, &sock_len);
                if (newSock < 0)
                {
                    perror("[-] connection not Accepted\n");
                    exit(-1);
                }
                printf("[+] connection Accepted\n");
                printf("New Client Connected\nPort No: %d\nIp: %s\n", ntohs(clientAddress.sin_port), inet_ntoa(clientAddress.sin_addr));
                pid = fork();
                printf("parent\n");
                if (pid == 0) /*** child process ***/
                {
                    printf("child\n");
                    while (1)
                    {
                        n = recv(newSock, data, MAX_MSG, 0);
                        if (n < 0)
                        {
                            perror("recv error \n");
                        }
                        if (n == 0)
                        {
                            break;
                        }
                        send(newSock, data, n, 0);
                        data[n] = '\0';
                        printf("Sent Message : %s\n", data);
                    }
                }
            }
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
        ```