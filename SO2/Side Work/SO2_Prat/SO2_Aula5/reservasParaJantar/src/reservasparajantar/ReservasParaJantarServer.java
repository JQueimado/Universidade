/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package reservasparajantar;

/**
 *
 * @author joao
 */
public class ReservasParaJantarServer {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        
        int regPort= 1099; 
        
        if (args.length !=1) {
            
	    System.out.println("Usage: java so2.rmi.PalavrasServer registryPort");
	    System.exit(1);
            
	}
        
        try{
            
            regPort = Integer.parseInt(args[0]);
            
            Reserva res = new ReservaImpl();
            
            java.rmi.registry.Registry regestry = java.rmi.registry.LocateRegistry.getRegistry(regPort);
            
            regestry.rebind("reserva", res);
            
            System.out.println("Bound RMI object in registry");

            System.out.println("servidor pronto");
            
        }catch (Exception e){
            
            e.printStackTrace();
            
        }
        
    }
    
}
