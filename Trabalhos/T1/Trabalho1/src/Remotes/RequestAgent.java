package Remotes;

public interface RequestAgent extends java.rmi.Remote{
    
    public int set_request( String name, String product ) throws java.rmi.RemoteException;
    
    public String[][] get_requests_for( String name ) throws java.rmi.RemoteException;
    
}
