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
public class ReservasParaJantarCliente {
    
    public static void main(String[] args){
        
        String regHost = "localhost";
	String regPort = "9000";  // porto do binder
	String comand= "";
        String nome = "";

        if (args.length >4 && args.length <3) {
	    System.out.println
		("Usage: java so2.rmi.PalavrasClient registryHost registryPort frase");
	    System.exit(1);
	}
        
        regHost= args[0];
	regPort= args[1];
        comand = args[2];
	
        if ( comand.compareTo("add") == 0 ){
            
            nome = args[3];
            
        }
        
        try{
            
            Reserva res = 
                    (Reserva) java.rmi.Naming.lookup("rmi://"+regHost+":"+regPort+"/reserva");
            
            if ( comand.compareTo("add") == 0 )
            {
                res.addReserva(nome);
                System.out.println("Added:"+nome);
                System.exit(0);
            }
            
            if ( comand.compareTo("list") == 0 )
            {
                System.out.println("List:" + res.list().toString());
                System.exit(0);
            }
            
            if ( comand.compareTo("number") == 0)
            {
                System.out.println("Size:" + res.count());
                System.exit(0);
            }
            
            System.out.println("comand not found");
            System.exit(1);
            
        }catch (Exception e){
            e.printStackTrace();
        }
        
    }
    
}
