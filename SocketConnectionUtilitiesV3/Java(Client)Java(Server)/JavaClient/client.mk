
CC = javac
MAKE = make
RM = rm

all : Client.java
	$(CC) Client.java
	java Client

clean : 
	$(RM) Client.class
	$(RM) Property.class

	



	
	

