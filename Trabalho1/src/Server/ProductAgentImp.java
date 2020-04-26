package Server;

import java.rmi.RemoteException;
import java.sql.SQLException;

public class ProductAgentImp extends java.rmi.server.UnicastRemoteObject implements Remotes.ProductAgent, java.io.Serializable{

    private DBManager database;
    
    public ProductAgentImp( DBManager database ) throws RemoteException{
        super();
        this.database = database;
    }
    
    @Override
    public String[] get_product(String product) throws RemoteException {
         try
        {
            return database.get_product(product);
        }
        catch( SQLException sqle )
        {
            System.err.println("[ER]:Sql Error on get_product");
            sqle.printStackTrace();
            return null;
        }
    }

    @Override
    public boolean add_product(String product) throws RemoteException {
        try
        {
            this.database.add_product(product);
            return true;
        }
        catch( SQLException sqle )
        {
            System.err.println("[ER]: Sql Error on add_product");
            sqle.printStackTrace();
            return false;
        }
        
    }
    
}
