
CC = cc
MAKE = make
RM = rm

all : server.c
	$(CC) -o server server.c
	./server
	
clean : 
	$(RM) server

	



	
	

