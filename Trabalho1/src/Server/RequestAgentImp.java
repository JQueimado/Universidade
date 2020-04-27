package Server;

import java.rmi.RemoteException;
import java.sql.SQLException;

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

    @Override
    public String[][] get_requests_for(String name) throws RemoteException {
        try
        {
            return database.get_requests(name);
        }
        catch( SQLException sqle )
        {
            sqle.printStackTrace();
            return null;
        }
    }
    
}
