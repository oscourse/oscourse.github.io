import java.rmi.*;

public interface ServerIF extends Remote
{
	public void callMeBack(ClientIF c) throws RemoteException;
}

