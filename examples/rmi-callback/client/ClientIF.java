import java.rmi.*;

public interface ClientIF extends Remote
{
	public void callBack() throws RemoteException;
}

