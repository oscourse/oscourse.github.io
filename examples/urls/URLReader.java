import java.net.*;
import java.io.*;

public class URLReader { 

	public static void main(String[] args) throws Exception { 
		// create a URL object
		URL yahoo = new URL("http://www.yahoo.com/");

		//Get its input stream
		BufferedReader in = new BufferedReader( 
				new InputStreamReader( 
					yahoo.openStream()
				));

		// read the website
		String inputLine; 
		while ((inputLine = in.readLine()) != null)
			System.out.println(inputLine);

		in.close(); 
	} 
} 

