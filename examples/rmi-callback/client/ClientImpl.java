import java.rmi.*; 
import java.rmi.server.*;

public class ClientImpl implements ClientIF 
{
	private int count;
	public ClientImpl()
	{ 
		count = 0; 
	}

	public void callBack()
	{ 
		count ++;
		System.out.println("Client callBack called " + count);
	}
}

