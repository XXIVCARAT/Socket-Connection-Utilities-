// A Java program for a Server
import java.net.*;
import java.io.*;

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

			socket = server.accept();

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
						//System.out.println(line.length());
						//System.out.println(line);
						
					}
					//System.out.println(line);
					//Run run = new Run(line);

				}
				catch(IOException i)
				{
					//System.out.println(i);
					in.close();
					socket.close();
					server.close();
					
					server = new ServerSocket(port);
					socket = server.accept();
					in = new DataInputStream(
					new BufferedInputStream(socket.getInputStream()));
				}
				
			}
			//System.out.println("Closing connection");
			}
			catch(NullPointerException e){
				in.close();
				socket.close();
				server.close();
				start(5000);
				
				
			}
			// close connection
			socket.close();
			in.close();
		}
		catch(IOException i)
		{
			System.out.println(i);
		}
		
	}

	public static void main(String args[])
	{
		Server server = new Server();
		server.start(5000);
	}
}

class Run{

	public Run(String command){
	
	try{
		runProcess(command);
		
	}
	
	catch (Exception e) {
            e.printStackTrace();
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
