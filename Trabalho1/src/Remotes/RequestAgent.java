package Remotes;

import java.util.List;

public interface RequestAgent extends java.rmi.Remote{
    
    public int set_request( String name, String product ) throws java.rmi.RemoteException;
    
}
