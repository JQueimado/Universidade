/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package reservasparajantar;

import java.rmi.server.UnicastRemoteObject;
import java.util.Vector;

/**
 *
 * @author joao
 */
public class ReservaImpl extends UnicastRemoteObject implements Reserva{
    
    private Vector<String> reservas;
    
    public ReservaImpl() throws java.rmi.RemoteException{
        super();
        
        this.reservas = new Vector();
        
    }
    
    public void addReserva (String nome) throws java.rmi.RemoteException{
        
        this.reservas.add(nome);
        
    }
    
    public Vector<String> list() throws java.rmi.RemoteException{
        
        return this.reservas;
        
    }
    
    public int count() throws java.rmi.RemoteException{
        
        return this.reservas.size();
        
    }
    
}
