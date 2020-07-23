package Server;

import Remotes.LoginAgent;
import java.rmi.RemoteException;

public class LoginAgentImp extends java.rmi.server.UnicastRemoteObject implements LoginAgent, java.io.Serializable {

    private DBManager mngr;
    
    public LoginAgentImp( DBManager mngr ) throws RemoteException{
        super();
        this.mngr = mngr;
    }
    
    @Override
    public int aprove(String name) throws RemoteException {
        try
        {
            int r = 0;
            if( !this.mngr.identifyUser(name) ){
                this.mngr.addUser(name);
                System.out.println("[OK]:Added User '" + name +"'");
                r += 1;
            }
            
            System.out.println("[OK]:User '" + name + "' logged in");
            return r+1;
        }
        catch( Exception e ){
            System.err.println("ERR");
            e.printStackTrace();
            return 0;
        }
    }
    
}
