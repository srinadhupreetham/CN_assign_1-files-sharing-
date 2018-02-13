#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8081
int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;  // sockaddr_in - references elements of the socket address. "in" for internet
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0},buffer1[1024] = {0};
    char *hello = "Hello from server here";
    FILE *fp;

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)  // creates socket, SOCK_STREAM is for TCP. SOCK_DGRAM for UDP
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // This is to lose the pesky "Address already in use" error message
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt))) // SOL_SOCKET is the socket layer itself
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;  // Address family. For IPv6, it's AF_INET6. 29 others exist like AF_UNIX etc.
    address.sin_addr.s_addr = INADDR_ANY;  // Accept connections from any IP address - listens from all interfaces.
    address.sin_port = htons( PORT );    // Server port to open. Htons converts to Big Endian - Left to Right. RTL is Little Endian

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,   //server_fd defines socket descriptor returned by socket()
                                 sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Port bind is done. You want to wait for incoming connections and handle them in some way.
    // The process is two step: first you listen(), then you accept()
    if (listen(server_fd, 3) < 0) // 3 is the maximum size of queue - connections you haven't accepted
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,   // address will hold clients information when accept returns
                       (socklen_t*)&addrlen))<0)                       //addrlen is pointer to size of client structure
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    valread = read(new_socket,buffer1,1024);//read information received into the buffer
    if (valread < 0)
        printf("error valread");
    printf("%s\n",buffer1 );
while(1)
{
    fp = fopen(buffer1, "r");
    if (fp == NULL)
    {
    	printf("File open error\n");
    	return 1;
    }

	while (1)
	{
		valread = fread(buffer,1,1024,fp); 
		if(valread > 0)
		{
			printf("sending read data\n");     
			write(new_socket,buffer,valread); //process of sending data to client from server
            printf("sent read data\n");
		}

		if(valread < 1024)
		{
			if (feof(fp))
				printf("End of file\n");  
			if (ferror(fp))
				printf("error reading\n");  // prints if error in reading occurs
			break;
		}
	}
    break;
}
    close(new_socket);
    return 0;
}
