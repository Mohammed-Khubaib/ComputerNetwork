- **(b) Implementation of concurrent echo server using connectionless socket system calls**
    - Server:
        
        ```c
        // (c) Implementation of concurrent echo server using connectionless socket
            // system calls
            // Server Program :
        #include <stdio.h>
        #include <sys/types.h>
        #include <sys/socket.h>
        #include <netinet/in.h>
        #include <arpa/inet.h>
        #include <stdlib.h>
        #include <unistd.h>
            int main(int argc, char *argv[])
        {
            int sockfd, rval, pid;
            char buff1[20], buff2[20];
            struct sockaddr_in server, client;
            int len;
            sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
            if (sockfd == -1)
            {
                perror("\n SOCK_ERR\n");
                exit(1);
            }
            server.sin_family = AF_INET;
            server.sin_addr.s_addr = inet_addr("192.168.0.5");
            server.sin_port = htons(3221);
            rval = bind(sockfd, (struct sockaddr *)&server, sizeof(server));
            if (rval != -1)
            {
                pid = fork();
                if (pid == 0)
                {
                    printf("\n child process executing\n");
                    printf("\n child process ID is:%d\n", getpid());
                    len = sizeof(client);
                    rval = recvfrom(sockfd, buff1, 20, 0, (struct sockaddr *)&client, &len);
                    if (rval == -1)
                    {
                        perror("\n RECV_ERR\n");
                        exit(1);
                    }
                    else
                    {
                        printf("\n received message is:%s\n", buff1);
                    }
                    rval = sendto(sockfd, buff1, sizeof(buff1), 0, (struct sockaddr *)&client, sizeof(client));
                    if (rval != -1)
                    {
                        printf("\n message sent successfully\n");
                    }
                    else
                    {
                        perror("\n SEND_ERR\n");
                        exit(1);
                    }
                }
                else
                    printf("\n parent process \n");
                printf("parent process ID is %d\n", getppid());
            }
            else
            {
                perror("\n BIND_ERR\n");
                exit(1);
            }
        }
        ```
        
    - Client:
        
        ```c
        // Client Program:
        #include <stdio.h>
        #include <sys/types.h>
        #include <sys/socket.h>
        #include <netinet/in.h>
        #include <arpa/inet.h>
        #include <stdlib.h>
        int main(int argc, char *argv[])
        {
            int sockfd, rval;
            char buff1[20], buff2[20];
            struct sockaddr_in server, client;
            int len;
            sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
            if (sockfd == -1)
            {
                perror("\n SOCK_ERR\n");
                exit(1);
            }
            server.sin_family = AF_INET;
            server.sin_addr.s_addr = inet_addr("192.168.0.5");
            server.sin_port = htons(3221);
            rval = bind(sockfd, (struct sockaddr *)&client, sizeof(client));
            if (rval == -1)
            {
                perror("\n BIND_ERR\n");
                exit(1);
            }
            printf("\n enter a message\n");
            scanf("%s", buff1);
            rval = sendto(sockfd, buff1, sizeof(buff1), 0, (struct sockaddr *)&server, sizeof(server));
            if (rval != -1)
            {
                printf("\n message sent succesfully\n");
            }
            else
            {
                perror("\n SESEND_ERR\n");
                exit(1);
            }
            len = sizeof(server);
            rval = recvfrom(sockfd, buff1, 20, 0, (struct sockaddr *)&server, &len);
            if (rval == -1)
            {
                perror("\n RECV_ERR\n");
                exit(1);
            }
            else
            {
                printf("\n received message is %s\n", buff1);
            }
        }
        ```