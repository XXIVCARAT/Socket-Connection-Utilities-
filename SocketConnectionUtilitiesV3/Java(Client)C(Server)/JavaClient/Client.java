// A Java program for a Client
import java.net.*;
import java.io.*;
import java.util.*;

public class Client
{
	// initialize socket and input output streams
	private Socket socket		 = null;
	private DataInputStream input = null;
	private DataOutputStream out	 = null;
	private int sentFlag = 0 ;
	
	



	// constructor to put ip address and port
	public Client(String address, int port , String [] args)
	{
		// establish a connection
		try
		{
			socket = new Socket(address, port);
			

			// sends output to the socket
			out = new DataOutputStream(socket.getOutputStream());
		}
		catch(UnknownHostException u)
		{
		
			if(Property.getMode()){
        			System.out.println(u);	
        		}
		}
		catch(IOException i)
		{
			if(Property.getMode()){
        			System.out.println(i);	
        		}
		}

		
		String outGoingMessage="";
		for(int i = 0 ; i < args.length ; i++){
		
			outGoingMessage=(new StringBuilder()).append(outGoingMessage).append(args[i]).toString(); 
			outGoingMessage=(new StringBuilder()).append(outGoingMessage).append(" ").toString(); 
		}
		try{
    				
			if(Property.getMode()){
				System.out.println(outGoingMessage);	
			}
			out.write(outGoingMessage.getBytes());
		} 
		catch (Exception e) {
			
			//e.printStackTrace();
			if(Property.getMode()){
				System.out.println("Not Connected....Make sure server is Running");	
			}
    			
		}

		// close the connection
		try
		{
			out.close();
			socket.close();
		}
		catch(Exception i)
		{
			if(Property.getMode()){
				System.out.println(i);	
			}
		}
	}
	
	
	
	public static void main(String []args){
		
		Property property = new Property();
		Client client = new Client(property.getHostname() , property.getPORT() , args);
		
	}

}

class Property{

	private String hostname;
	private String PORT;
	private static String debugFlag;
	
	public Property(){
		Properties prop = new Properties();
		String fileName = "/home/main/SocketConnectionUtilitiesV4/Java(Client)C(Server)/JavaClient/JavaClient.cfg";
		try (FileInputStream fis = new FileInputStream(fileName)) {
		    prop.load(fis);
		} 
		catch (FileNotFoundException ex) {
		    
		} 
		catch (IOException ex) {
		    
		}
		this.hostname = prop.getProperty("HOSTNAME");
		this.PORT = prop.getProperty("PORT");
		this.debugFlag = prop.getProperty("DEBUGMODE");
		
	}
	
	public String getHostname(){
	
		return hostname;
	}
	public int getPORT(){
	
		
		return  Integer.parseInt(PORT.trim());
		
		
	}
	public static boolean getMode(){
	
		
		if(Integer.parseInt(debugFlag.trim())==1){
			return true;
		}
		return false;
		
	}
}

