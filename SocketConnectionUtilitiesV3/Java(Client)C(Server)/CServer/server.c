
#include <netinet/in.h>

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <sys/socket.h>

#include <unistd.h>

#include <stdbool.h>

#include<signal.h>

#define configFileLocation "/home/main/SocketConnectionUtilitiesV4/Java(Client)C(Server)/CServer/serverC.cfg"

#define STRING_LENGTH 1024223

#define SMALLER_STRING_LENGTH 1024



int server_fd=0, new_socket=0, valread=0,opt = 1;
struct sockaddr_in address;
int addrlen = sizeof(address);
char buffer[STRING_LENGTH] = {0};



int getPort() { 
	
	FILE *file;
	file = fopen(configFileLocation, "r");
	
	char const *desired_name = "PORT";
	
	char name[SMALLER_STRING_LENGTH];
	char val[SMALLER_STRING_LENGTH];

	while (fscanf(file, "%127[^=]=%127[^\n]%*c", name, val) == 2) {
		if (0 == strcmp(name, desired_name)) {
		

			return atoi(strdup(val));
		}
	}
	return 0;
}





bool getMode()
{
	FILE *ini_file;
	int debugFlag = 0 ;
	ini_file = fopen(configFileLocation, "r");
	if(fscanf(ini_file, "DEBUGMODE=%d", &debugFlag) == 1)
	{	
  		if(debugFlag==1){
  			return true;
  		}
	}
	
	return false;
}

void startSocket() {

  // Creating socket file descriptor
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) ==
    0) {
    if(getMode()){
    	perror("socket failed");
    }
    exit(EXIT_FAILURE);
  }

  // Forcefully attaching socket to the port 5000
  if (setsockopt(server_fd, SOL_SOCKET,
      SO_REUSEPORT, & opt,
      sizeof(opt))) {
		  if(getMode()){
		  	perror("setsockopt");
		  }
      exit(EXIT_FAILURE);
  }
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(getPort());

  // Forcefully attaching socket to the port 5000
  if (bind(server_fd, (struct sockaddr * ) & address,
      sizeof(address)) <
    0) {
    if(getMode()){
    	perror("bind failed");
    }
    exit(EXIT_FAILURE);
  }
  if (listen(server_fd, 3) < 0) {
  	if(getMode()){
    	perror("listen");
    }
    exit(EXIT_FAILURE);
  }
  if ((new_socket = accept(server_fd, (struct sockaddr * ) & address,
      (socklen_t * ) & addrlen)) <
    0) {
    if(getMode()){
    	perror("accept");
    }
    exit(EXIT_FAILURE);
  }
  
  
}

void reconnectSocket(){

	if (listen(server_fd, 3) < 0) {
		if(getMode()){
	    	perror("listen");
	    }
	    exit(EXIT_FAILURE);
	}
	if ((new_socket = accept(server_fd, (struct sockaddr * ) & address,
	(socklen_t * ) & addrlen)) <
	0) {
		if(getMode()){
			perror("accept");
		}
	exit(EXIT_FAILURE);
	}

}

void handle_sigint()
{	
	if(getMode()){
		printf("Closing the Socket and Shutting down the server \n");
	}
	close(new_socket);
	shutdown(server_fd, SHUT_RDWR);
	exit(0);
}

int main(int argc, char const * argv[]){


	startSocket();
	signal(SIGINT, handle_sigint);

	while(true){
		
		valread = read(new_socket, buffer, STRING_LENGTH);
		
		if (valread != 0) {

      			system(buffer);

      			printf("\n");

      			memset(buffer, 0, STRING_LENGTH);

    		}
    		
    		else if (valread == -1 || valread == 0){
    		
    			//Starts listening for new Client
    			reconnectSocket();
    			
    		}
	
	}

}


