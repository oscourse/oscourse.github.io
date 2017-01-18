import java.net.*; 
import java.io.*; 
public class EchoClient { 

public static void main(String[] args) throws IOException 
{
	InetAddress addr = InetAddress.getByName("diablo.cs.fsu.edu");

	// Create a socket and connect to remote server
	Socket socket = new Socket(addr, EchoServer.PORT); 
	
	try { 
		// Get the input stream
		BufferedReader in = new BufferedReader( 
			new InputStreamReader(socket.getInputStream())); 

		// Get the output stream 	
		PrintWriter out = new PrintWriter( 
			new BufferedWriter( 
				new OutputStreamWriter(
					socket.getOutputStream())
				), true); 

		for(int i = 0; i < 10; i ++) {
			// Write to server
			out.println("Hello " + i); 

			// Read echo from server
			String str = in.readLine();
			System.out.println(str); 
		} 
		out.println("END"); 

	} finally {socket.close(); } 

}

}
