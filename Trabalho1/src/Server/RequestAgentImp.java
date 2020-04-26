package Server;

import java.rmi.RemoteException;

public class RequestAgentImp extends java.rmi.server.UnicastRemoteObject implements Remotes.RequestAgent, java.io.Serializable{

    private DBManager database;
    
    public RequestAgentImp( DBManager database ) throws RemoteException{
        super();
        this.database = database;
    }

    @Override
    public int set_request(String name, String product) throws RemoteException {
        try
        {
            return this.database.add_request(name, product);
        }
        catch( Exception e )
        {
            e.printStackTrace();
            return -1;
        }
    }
    
}
