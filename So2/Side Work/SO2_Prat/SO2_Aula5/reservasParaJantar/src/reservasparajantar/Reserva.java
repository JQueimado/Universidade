/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package reservasparajantar;

import java.util.Vector;

/**
 *
 * @author joao
 */
public interface Reserva extends java.rmi.Remote {
    
    public void addReserva (String nome) throws java.rmi.RemoteException;
    
    public Vector<String> list() throws java.rmi.RemoteException;
    
    public int count() throws java.rmi.RemoteException;
    
}
