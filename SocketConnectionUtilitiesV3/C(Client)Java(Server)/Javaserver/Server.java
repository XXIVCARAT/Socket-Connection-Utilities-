// A Java program for a Server
import java.net.*;
import java.io.*;
import java.util.*;

public class Server
{
	//initialize socket and input stream
	private Socket		 socket = null;
	private ServerSocket server = null;
	private DataInputStream in	 = null;

	// constructor with port
	public void start(int port)
	{
		// starts server and waits for a connection
		try
		{
			server = new ServerSocket(port);
			if(Property.getMode()){
				System.out.println("Server Started Waiting for client");
			}

			socket = server.accept();
			if(Property.getMode()){
				System.out.println("Client Accepted");
			}
			in = new DataInputStream(
				new BufferedInputStream(socket.getInputStream()));

			String line = "";

			// reads message from client until "Over" is sent
			try{
			while (!line.equals("Close"))
			{
				try
				{
					line = in.readLine();
					if(line!= null){
						
						Run run = new Run(line);
						
					}
					

				}
				catch(IOException i)
				{
					
					in.close();
					socket.close();
					server.close();
					
					server = new ServerSocket(port);
					socket = server.accept();
					in = new DataInputStream(
					new BufferedInputStream(socket.getInputStream()));
					
					socket = server.accept();
					
				}
				
			}
			
			}
			catch(NullPointerException e){
				in.close();
				socket.close();
				server.close();
				start(port); 
				
				socket = server.accept();
				
			}
			// close connection
			socket.close();
			in.close();
		}
		catch(IOException i)
		{
			
			if(Property.getMode()){
				System.out.println(i);
			}
		}
		
	}

	public static void main(String args[])
	{
		Server server = new Server();
		server.start(new Property().getPORT());
	}
}

class Run{

	public Run(String command){
	
	try{
		runProcess(command);
		
	}
	
	catch (Exception e) {
            //e.printStackTrace();
            if(Property.getMode())
            {
            	//Add Logger of e.printStackTrace()
            System.out.println("File not found");
            }
        }	
		
	}
	private static void runProcess(String command) throws Exception {
	try{
        Process pro = Runtime.getRuntime().exec(command);
        printLines(pro.getInputStream());
        printLines(pro.getErrorStream());
        pro.waitFor();
        }
        catch(NullPointerException u){
        
        
        
        }
        
      }
      
      private static void printLines(InputStream ins) throws Exception {
        String line = null;
        BufferedReader in = new BufferedReader(
            new InputStreamReader(ins));
        while ((line = in.readLine()) != null) {
            System.out.println(line);
        }
      }
}

class Property{

	
	private String PORT;
	private static String debugFlag;
	
	public Property(){
		Properties prop = new Properties();
		String fileName = "/home/main/SocketConnectionUtilitiesV4/C(Client)Java(Server)/Javaserver/javaServer.cfg";
		try (FileInputStream fis = new FileInputStream(fileName)) {
		    prop.load(fis);
		} 
		catch (FileNotFoundException ex) {
		    
		} 
		catch (IOException ex) {
		    
		}
		
		this.PORT = prop.getProperty("PORT");
		this.debugFlag = prop.getProperty("DEBUGMODE");
		
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

