import java.rmi.*;
import java.rmi.server.*;

public class ServerImpl 
	extends UnicastRemoteObject
	implements ServerIF 
{
	public ServerImpl() throws RemoteException 
	{
       		super();
	}

	public void callMeBack(ClientIF c) throws RemoteException 
	{
		System.out.println("Making Client callback\n");
		c.callBack();
	}
}

