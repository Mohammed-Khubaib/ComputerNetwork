# CN lab programs :

- **1.Implement a simple DNS**
    
    ```c
    // 1.Implement a simple DNSs
    
    #include <stdio.h>
    #include <netdb.h>
    #include <sys/types.h>
    #include <netinet/in.h>
    #include<sys/socket.h>
    #include<arpa/inet.h>
    int main(int argc,char *argv[])
    {
    struct hostent *h;
    if(argc!=2)
    { /*error check the command line*/
    printf(stderr,"usage:getpid address\n");
    exit(1);
    }
    if((h=gethostbyname(argv[1]))==NULL)
    { /*get the host info*/
    perror("gethostbyname");
    exit(1);
    }
    printf("Host name : %s\n",h->h_name);
    printf("IP Address : %s\n",inet_ntoa(*((struct in_addr *)h->h_addr)));
    return 0;
    }
    ```