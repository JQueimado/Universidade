
package Server;

import java.rmi.registry.*;
import java.rmi.*;

public class RMIController {
    
    private Registry registry;
    
    /* Constructors */
    
    public RMIController( int port ) throws Exception{
        this.registry = java.rmi.registry.LocateRegistry.createRegistry(port);
    }
    
    public RMIController() throws Exception{
        this(1099);
    }
    
    public void addRemoteObject(Remote obj, String name) throws RemoteException{
        this.registry.rebind(name, obj);
    }
    
}