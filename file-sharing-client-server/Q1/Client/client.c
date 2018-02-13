// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8081

int main(int argc, char const *argv[])
{
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hey I'm your client";
    char buffer[1024] = {0};
    char buffer1[1024]={0};
    FILE *fp;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)//SOCK_STREAM defines TCP here
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr)); // to make sure the struct is empty. Essentially sets sin_zero as 0
                                                // which is meant to be, and rest is defined below

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Converts an IP address in numbers-and-dots notation into either a 
    // struct in_addr or a struct in6_addr depending on whether you specify AF_INET or AF_INET6.
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
   

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)  // connect to the server address
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    printf("Enter the file name you want to download from the server :");
    fgets(buffer1,1024,stdin);//fgets takes input while client is running
    buffer1[strlen(buffer1)-1]=0;

    send(sock,buffer1,strlen(buffer1),0);  //send the message
                                          //sock is socket connected here
                                         //buffer1 is a buffer which sends data
                                        // here flag bit is 0

    fp = fopen(buffer1,"a");

    while ((valread = read(sock,buffer,1024))>0)//valread::no of bytes received by client
    {
        printf ("Connected with server and successfully recieving data......\n"); //receive message back from server, into the buffer
        fwrite(buffer,1,valread,fp);
        printf ("File received\n");
    }
    if(valread < 0)
        printf("File not found (or) Read error1\n");
    return 0;
}