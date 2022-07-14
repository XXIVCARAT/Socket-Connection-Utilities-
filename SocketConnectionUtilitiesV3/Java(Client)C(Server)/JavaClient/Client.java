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
	
	
	



	// constructor to put ip address and port
	public Client(String address, int port , String [] args)
	{
		// establish a connection
		try
		{
			socket = new Socket(address, port);
			

			// takes input from terminal
			input = new DataInputStream(System.in);

			// sends output to the socket
			out = new DataOutputStream(socket.getOutputStream());
		}
		catch(UnknownHostException u)
		{
			System.out.println(u);
		}
		catch(IOException i)
		{
			System.out.println(i);
		}

		
		String cmd="";
		for(int i = 0 ; i < args.length ; i++){
		
			cmd=(new StringBuilder()).append(cmd).append(args[i]).toString(); 
			cmd=(new StringBuilder()).append(cmd).append(" ").toString(); 
		}
		try{
    				
    				System.out.println(cmd);
    				out.write(cmd.getBytes());
    			} 
   			catch (IOException e) {
        			// TODO Auto-generated catch block
        			//e.printStackTrace();
        			System.out.print("Not Connected....Make sure server is Running");	
    			
		}

		// close the connection
		try
		{
			input.close();
			out.close();
			socket.close();
		}
		catch(IOException i)
		{
			System.out.println(i);
		}
	}
	
	
	
	public static void main(String []args){
		
		Property property = new Property();
		Client client = new Client(property.getHostname() , property.getPORT() , args);
		//Client client = new Client("localhost" , 5000 , args);
	}

}

class Property{

	private String hostname;
	private String PORT;
	
	public Property(){
		Properties prop = new Properties();
		String fileName = "ip.config";
		try (FileInputStream fis = new FileInputStream(fileName)) {
		    prop.load(fis);
		} 
		catch (FileNotFoundException ex) {
		    
		} 
		catch (IOException ex) {
		    
		}
		this.hostname = prop.getProperty("hostname");
		this.PORT = prop.getProperty("PORT");
	}
	
	public String getHostname(){
	
		return hostname;
	}
	public int getPORT(){
	
		
			return  Integer.parseInt(PORT.trim());
		
		
	}
}

