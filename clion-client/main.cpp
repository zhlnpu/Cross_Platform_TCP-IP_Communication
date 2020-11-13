#include<stdio.h>
#include<string.h>	//strlen
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include<pthread.h> //for threading , link with lpthread

void *connection_handler(void *);
char *message , server_reply[2000];

int main(int argc , char *argv[])
{
    int socket_desc;
    struct sockaddr_in server;

    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons( 27015 );

    //Connect to remote server
    if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("connect error");
        return 1;
    }

    puts("Connected\n");

    //Send some data
    message = "GET / HTTP/1.1\r\n\r\n";
    if( send(socket_desc , message , strlen(message) , 0) < 0)
    {
        puts("Send failed");
        return 1;
    }
    puts("Data Send\n");

    //Receive a reply from the server
    if( recv(socket_desc, server_reply , 2000 , 0) < 0)
    {
        puts("recv failed");
    }
    puts("Reply received\n");
    puts(server_reply);

    pthread_t sniffer_thread;

    while (true) {
        char input[6];
        scanf("%s", input);
        if (strcmp(input, "exit") == 0)
            break;

        if (strcmp(input, "test") == 0)
        {
            if( pthread_create( &sniffer_thread , NULL ,  connection_handler , (void*) socket_desc) < 0)
            {
                perror("could not create thread");
                return 1;
            }
        }
    }
    return 0;
}

void *connection_handler(void *socket_desc)
{
    int read_size;

    int sock = *(int*)socket_desc;
while ( (read_size= recv(sock, server_reply , 2000 , 0) )>0)
    {
        send(sock , message , strlen(message) , 0) ;

            puts(message            );
    }

    return 0;
}