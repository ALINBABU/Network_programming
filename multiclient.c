#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h> 
#include <unistd.h>
#include <errno.h>
#define BUF_SIZE 2000 
  
int main() 
{  
	struct sockaddr_in addr, cl_addr;  
	int sockfd, ret;  
	char buffer[BUF_SIZE];  //Declaring buffer
	struct hostent * server;
	char * serverAddr;
	//Getiing server ip address
	printf("Enter server ip address\n");
	scanf("%c",serverAddr);         
	sockfd = socket(AF_INET, SOCK_STREAM, 0);  //Socket Creation
	if (sockfd < 0) 
	{  
		printf("Error creating socket!\n");  
		exit(1);  
	}  
	printf("Socket created...\n");   
	memset(&addr, 0, sizeof(addr));  
	addr.sin_family = AF_INET;  
	addr.sin_addr.s_addr = inet_addr(serverAddr);
	addr.sin_port = htons(5000);     
	ret = connect(sockfd, (struct sockaddr *) &addr, sizeof(addr));  //Connecting socket
	if (ret < 0) 
	{  
		printf("Error connecting to the server!\n");  
		exit(1);  
	}  
	printf("Connected to the server...\n");  
	memset(buffer, 0, BUF_SIZE);
	printf("Enter your message(s): ");
	while (fgets(buffer, BUF_SIZE, stdin) != NULL) 
	{
		ret = sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));  //Sending message  
		if (ret < 0) 
		{  
			printf("Error sending data!\n\t-%s", buffer);  
		}
		ret = recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);  //Receiving message
		if (ret < 0) 
		{  
			printf("Error receiving data!\n");    
		} 
		else 
		{
			printf("Received: ");
			fputs(buffer, stdout);
			printf("\n");
		}  
	}		     
	return 0;    
}  
