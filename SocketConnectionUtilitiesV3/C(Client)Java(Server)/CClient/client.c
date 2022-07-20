// Client side C/C++ program to demonstrate Socket
// programming
#include <stdlib.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdbool.h>
#define STRING_LENGTH 1024223
#define SMALLER_STRING_LENGTH 1024
#define configFileLocation "/home/main/SocketConnectionUtilitiesV4/C(Client)Java(Server)/CClient/clientC.cfg"





char *getHostName() { 
	
	FILE *file;
	file = fopen(configFileLocation, "r");
	
	char const *desired_name = "HOSTNAME";
	
	char name[SMALLER_STRING_LENGTH];
	char val[SMALLER_STRING_LENGTH];

	while (fscanf(file, "%127[^=]=%127[^\n]%*c", name, val) == 2) {
		if (0 == strcmp(name, desired_name)) {
		

			return strdup(val);
		}
	}
	return "";
}

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





int main(int argc, char const* argv[])
{
	int sock = 0, 
	valread = 0, 
	client_fd = 0,
	hostname = 0,
	len = 0;
	
	struct sockaddr_in serv_addr;
	struct hostent *host_entry;
	
	char *IPbuffer;
    	
    	bool debugMode;
    	
    	debugMode = getMode();
    	
    	if(debugMode){
    	printf("Port=");
    	printf("%d\n" , getPort());
    	printf("HostName=");
    	printf("%s\n" , getHostName());
    	}
  
    	
	// To retrieve host information
    	host_entry = gethostbyname(getHostName());
    
  
    	// To convert an Internet network
    	// address into ASCII string
    	IPbuffer = inet_ntoa(*((struct in_addr*)
                           host_entry->h_addr_list[0]));
                           
	char buffer[STRING_LENGTH] = { 0 };
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		if(debugMode){
			printf("\n Socket creation error \n");
			return -1;
		}
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(getPort());

	// Convert IPv4 and IPv6 addresses from text to binary
	// form
	if (inet_pton(AF_INET, IPbuffer, &serv_addr.sin_addr)
		<= 0) {
		if(debugMode){
			printf(
				"\nInvalid address/ Address not supported \n");
		}
		return -1;
	}

	if ((client_fd
		= connect(sock, (struct sockaddr*)&serv_addr,
				sizeof(serv_addr)))
		< 0) {
		if(debugMode){
			printf("\nConnection Failed \n");
		}
		return -1;
	}
	
	
	for(int i = 1 ; i < argc ; i++)
	{
		
		len = len + strlen(argv[i]);	
		len++;	
	}
	
	len--;
	char outGoingMessage[len];
	memset(outGoingMessage , 0 ,len);
	
	for(int i = 1 ; i < argc ; i++)
	{
		char commandLineInput[STRING_LENGTH];
		strcpy(commandLineInput , argv[i]);
		strcat(outGoingMessage , commandLineInput);
		strcat(outGoingMessage , " ");
		memset(commandLineInput , 0 , STRING_LENGTH);
	}
	
	
	
	
	send(sock, outGoingMessage, len, 0);
	memset(outGoingMessage , 0 ,len);
	close(client_fd);
	return 0;
}


