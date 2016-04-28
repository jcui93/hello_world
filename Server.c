#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

int main( int argc, char *argv[] )
{
	int serverSocket, client, portNum;
	char command[256];
	struct sockaddr_in server_addr, client_addr;
	int index = 0;


	//Create the server socket 
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);

	//Initialize socket structure
	bzero((char *) &server_addr, sizeof(server_addr));

	//Set the port number 
	portNum = 4444;
	
	//Declare the socket protocols and port num
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(portNum);

	//Check for an error when binding the server to the client
	if (bind(serverSocket, (struct sockaddr *) &server_addr,sizeof(server_addr)) < 0)
	{
		perror("ERROR on binding");
		return(1);
	}
	
	//Listen for clients that want to connect to the server
	listen(serverSocket, 20);

	//Store the size of the client address into the size variable
	int size = sizeof(client_addr);
	
	//Accept the connection 
	client = accept(serverSocket, (struct sockaddr *)&client_addr, &size);
	
	//Initialize the buffer
	bzero(command, 256);
	
	//Read the data being sent from the client and store it in the command variable
	read(client, command, 255);

	while(command)
	{
		
		accept(serverSocket, (struct sockaddr *)&client_addr, &size);
		read(client, command, 255);
		
		if (*command != '5')
		{
			printf("%s\n",command); 
			close(client);                      
		}
		
	 	else if (*command == '5')
		{
			printf("Disconnected\n");
			return(1);
		}
	
	}

	close(client);

	return 0;


}
