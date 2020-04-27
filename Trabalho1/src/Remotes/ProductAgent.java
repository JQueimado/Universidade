package Remotes;

public interface ProductAgent extends java.rmi.Remote {
    
    // Searches for a product in the system
    public String[] get_product( String product ) throws java.rmi.RemoteException;
    
    // Adds a product to the system
    public boolean add_product( String product ) throws java.rmi.RemoteException;
    
    public boolean set_availabe( String product, String loc ) throws java.rmi.RemoteException;
    
}
