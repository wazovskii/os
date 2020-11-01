#include<stdio.h>
#include<stdlib.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h>    //inet_addr

int main(int argc , char *argv[])
{
    
    int socket_desc;
    struct sockaddr_in server;
    char *message , server_reply[500],server_reply2[500];
    
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Не могу создать розетку");
    }
        
    //server.sin_addr.s_addr = inet_addr("127.0.0.0");
    server.sin_family = AF_INET;
    server.sin_port = htons( 8000 );

    //Connect to remote server
    if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("Ошибка подключения");
        return 1;
    }
    
    puts("Подключено\n");
    //pause(5000);
    //Send some data
//    message = "GET / HTTP/1.1\r\n\r\n";
//    if( send(socket_desc , message , strlen(message) , 0) < 0)
//    {
//        puts("Send failed");
//        return 1;
//    }
//    puts("Data Send\n");
//
    for(int i=0; i<2;i++)
    {
        if( recv(socket_desc, server_reply , 2000 , 0) < 0)
        {
            puts("Не принял");
        }
        puts("Пришел ответ\n");
        puts(server_reply);
    }
    char buff[200];
///    char *ukaz=NULL;
    scanf("%99[^\n]",buff);
    message=buff;
        if( send(socket_desc , message , strlen(message) , 0) < 0)
        {
            puts("Не отправил");
            return 1;
        }
        if( recv(socket_desc, server_reply2 , 2000 , 0) < 0)
        {
            puts("Не принял");
        }
        puts("Пришел ответ\n");
        puts(server_reply2);

    
    return 0;
}
