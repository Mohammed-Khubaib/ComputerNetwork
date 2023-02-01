1. Implementation of Iterative Daytime server using Connection Oriented(TCP).
2. Implementation of iterative echo server using connection oriented socket system calls (TCP)
3. Implementation of concurrent echo server using connection oriented socket system calls(TCP)


# Socket Programming

<aside>
👉🏻 Server

1. socket(Domain,Type,Protocol):
    - Domain :
        - it will specify ipv4 or ipv6.
        - AF_INET is used for ipv4
        - AF_INET6 is used for ipv6
    - Type:
        - if we use TCP as Type we use **SOCK_STREAM**.
        - if we use UDP as Type we use **SOCK_DGRAM**.
    - protocol:
        - we will give 0
    - Example :
        - `socket(AF_INET,SOCK_STREAM,0);`

---

1. Bind()
    - it assigns the socket address to the server:
    - socket Address :ip address of 32 bit with 16 bit Port number (ip+port)
2. Listen() :
    1. it waits for the request in passive mode 
    2. onces it gets the connection request form the server it will add it to the queue [aka Backlog] amd pass it to Accept() function.
    - it takes socket file Discrepter i.e socket address.
    1. if the queue gets full it will refuse the client to connect
3. Accept() :
    1. it will establish the connection.
4. send()↔ Recieve() :
    1. sending and recieving process
5. close() :terminates the connection.
</aside>

<aside>
👉🏻 Client :

1. socket(Domain,Type,Protocol):
    - same as server
    
    ---
    
2. connect() :
    1. it takes the socket address of the server and try to connect to the server.

---

1. close() :terminates the connection.
</aside>