
CC = javac
MAKE = make
RM = rm

all : Server.java
	$(CC) Server.java
	java Server
	
clean : 
	$(RM) Server.class
	$(RM) Run.class
	

	



	
	

