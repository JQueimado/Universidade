package Client;

import Remotes.LoginAgent;
import Remotes.RequestAgent;
import Remotes.ProductAgent;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.Naming;

public class RemoteManager {
    
    private String uri = "rmi://";
    private Registry registry;      
    
    private String name;
    
    private LoginAgent la;
    private RequestAgent ra;
    private ProductAgent pa; 
    
    /* Constructors */
    
    public RemoteManager( String host, int port ) throws Exception{
        this.uri += host + ":" + port +"/";
        
        // Get server registry
        this.registry = LocateRegistry.getRegistry("localhost", 1099);
        
        this.la = (LoginAgent) Naming.lookup(uri +"loguser");
        this.ra = null;
        this.pa = null;
        
        this.name = "";
    }
    
    public RemoteManager() throws Exception{
        this( "localhost", 1099 );
    }
    
    /* Methods */
    
    // Login
    public int login( String name ) throws Exception{

        int ret = this.la.aprove(name);

        if ( ret == 0 )
            throw new Exception("Login faild");
        
        // Set other objects
        this.ra = (RequestAgent) Naming.lookup(uri + "requestagent");
        this.pa = (ProductAgent) Naming.lookup(uri + "productagent");
        
        this.name = name;
        
        return ret-1;
    }
    
    // Set a request
    public int set_request(String product ) throws Exception{
        
        return this.ra.set_request(this.name, product);
        
    }
    
    // Search product
    public String[] get_product( String p_name ) throws Exception
    {   
        return this.pa.get_product(p_name);
    }
    
    // Add product and request
    public int add_product_request( String p_name ) throws Exception {
        this.pa.add_product( p_name );
        return set_request( p_name );
    }
    
}
