
CC = cc
MAKE = make
RM = rm

all : client.c
	$(CC) -o client client.c
	
clean : server
	$(RM) client
	



	
	

