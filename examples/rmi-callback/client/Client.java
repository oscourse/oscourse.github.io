import java.rmi.*;
import java.rmi.server.*;

public class Client 
{
	public static void main(String args[])
	{
		try {
			ClientIF c =new ClientImpl();
			UnicastRemoteObject.exportObject(c);
			
			ServerIF s =(ServerIF) Naming.lookup("rmi://diablo/Service");

			for(int i=0; i<10; i++)
				s.callMeBack(c);

		} catch (Exception e) {

			System.out.println("Exception " + e);

		} finally {
			System.exit(0);
		}
	}
}

