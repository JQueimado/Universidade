package Client;

import Remotes.LoginAgent;

public class RemoteManager {
    
    private String uri = "rmi://";
    
    /* Constructors */
    
    public RemoteManager( String host, int port ){
        this.uri += host + ":" + port +"/";
    }
    
    public RemoteManager(){
        this.uri += "localhost:1099/";
    }
    
    /* Methods */
    
    public int login( String name ) throws Exception{
        LoginAgent log = (LoginAgent) java.rmi.Naming.lookup(uri +"loguser");

        int ret = log.aprove(name);

        if ( ret == 0 )
            throw new Exception("Login faild");

        /* Insert other remote objects connections */

        return ret-1;
    }
    
}
