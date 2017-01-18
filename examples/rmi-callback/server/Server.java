import java.rmi.*;

public class Server {
	public static void main(String args[]) {

		try {

			ServerIF s = new ServerImpl();
			Naming.rebind( "rmi://diablo/Service", s );

		} catch ( Exception e ) {

		       System.out.println( "Trouble: " + e );

		}
	}
}

