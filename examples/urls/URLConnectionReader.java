import java.net.*;
import java.io.*;

public class URLConnectionReader { 

	public static void main(String[] args) throws Exception { 

		// create a URL object 
		URL yahoo = new URL("http://www.yahoo.com/");

		// Open a connection
		URLConnection yc = yahoo.openConnection();
		
		// Get its input stream
		BufferedReader in = new BufferedReader( 
						new InputStreamReader(
						   yc.getInputStream()
					   )); 
		// read the website
		String inputLine; 
		while ((inputLine = in.readLine()) != null) 
			System.out.println(inputLine); 

		in.close(); 
	} 
}

