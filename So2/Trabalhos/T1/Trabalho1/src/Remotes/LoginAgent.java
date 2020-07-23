package Remotes;

public interface LoginAgent extends java.rmi.Remote {
    
    public int aprove( String name ) throws java.rmi.RemoteException;
    
}
