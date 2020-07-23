
package Server;

import java.rmi.registry.*;
import java.rmi.*;
import java.util.Properties;

public class RMIController {
    
    private Registry registry;
    private Properties properties;
    
    /* Constructors */
    
    public RMIController( int port, Properties properties ) throws Exception{
        this.registry = java.rmi.registry.LocateRegistry.createRegistry(port);
        this.properties = properties;
    }
    
    public RMIController( Properties properties ) throws Exception{
        this( Integer.parseInt( properties.getProperty("def-regport") ), properties );
    }
    
    public void addRemoteObject(Remote obj, String name) throws RemoteException{
        this.registry.rebind(name, obj);
    }
    
    public Object getRemote( String name ) throws Exception{
        
        String lookuri = "rmi://localhost:"+ properties.getProperty("def-regport") +"/" + name;
        
        return java.rmi.Naming.lookup(lookuri);
        
    }
    
}
