package Client;

import Remotes.LoginAgent;
import Remotes.RequestAgent;
import Remotes.ProductAgent;
import java.rmi.*;
import java.util.Properties;

public class RemoteManager {
    
    private String uri = "rmi://";    
    
    private String name;
    private Properties properties;
    private Storage storage;
            
    private LoginAgent la;
    private RequestAgent ra;
    private ProductAgent pa; 
    
    /* Constructors */
    
    public RemoteManager( String host, String port, Properties properties ) throws Exception{
        this.uri += host + ":" + port +"/";
        
        this.properties = properties;
        this.storage = new Storage( properties.getProperty("storage-filename") );
        
        this.la = (LoginAgent) Naming.lookup(uri + properties.getProperty("name-log"));
        this.ra = null;
        this.pa = null;
        
        this.name = "";
    }
    
    public RemoteManager( Properties properties ) throws Exception{
        this( properties.getProperty("def-reghost"), properties.getProperty("def-regport"), properties );
    }
    
    /* Methods */
    
    public Storage get_storage(){
        return this.storage;
    }
    
    // Login
    public int login( String name ) throws Exception{

        String[] aux = {"aprove", name };
        this.storage.store_send_msg( aux );
        
        int ret = this.la.aprove(name);

        aux[1] = String.valueOf(ret);
        this.storage.store_recv_msg(aux);
        
        if ( ret == 0 )
            throw new Exception("Login failed");
        
        // Set other objects
        this.ra = (RequestAgent) Naming.lookup(uri + properties.getProperty("name-request") );
        this.pa = (ProductAgent) Naming.lookup(uri + properties.getProperty("name-product"));
        
        this.name = name;
        
        return ret-1;
    }
    
    // Set a request
    public int set_request(String product ) throws Exception{
        String[] aux = { "set_request", product };
        this.storage.store_send_msg(aux);
        
        int r = this.ra.set_request(this.name, product);     
        
        aux[1] = String.valueOf(r);
        this.storage.store_recv_msg(aux);
        
        return r;
    }
    
    // Set available
    public boolean set_avalable( String product, String loc ){
        try
        {
            String[] aux = { "set_avalable", product, loc};
            this.storage.store_send_msg(aux);
            
            boolean r = this.pa.set_availabe(product, loc);
            
            aux[1] = String.valueOf(r);
            this.storage.store_recv_msg(aux);
            
            return r;
        }
        catch( RemoteException re)
        {
            re.printStackTrace();
            return false;
        }
    }
    
    public String[][] get_requests() throws Exception{
        
        String[] aux = { "get_requests", this.name };
        this.storage.store_send_msg(aux);
        
        String[][] r =  this.ra.get_requests_for( this.name );
        
        this.storage.store_recv_msg(aux, r);
        
        return r;
    }
    
    // Search product
    public String[] get_product( String p_name ) throws Exception{   
        String[] aux = { "get_product", p_name, this.name };
        this.storage.store_send_msg(aux);
        
        String[] r = this.pa.get_product(p_name);
        
        return r;
    }
    
    // Add product and request
    public int add_product_request( String p_name ) throws Exception {
        String[] aux = { "add_product", p_name, this.name };
        this.storage.store_send_msg(aux);
        
        boolean r = this.pa.add_product( p_name );
        
        aux[1] = String.valueOf(r);
        this.storage.store_recv_msg(aux);
        
        return set_request( p_name );
    }
}
