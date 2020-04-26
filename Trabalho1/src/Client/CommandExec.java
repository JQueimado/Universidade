package Client;

import java.io.IOException;
import java.util.List;
import java.util.Scanner;

public class CommandExec {
    
    private RemoteManager rm;
    private String loged_user;
    
    private Scanner scanner;
    
    public CommandExec( Scanner scanner) throws Exception{
        this.rm = new RemoteManager();
        this.scanner = scanner;
    }
    
    /* AUX methods */
    private String read()throws IOException{
        return this.scanner.nextLine();
    }
    
    /* Commands */
    // Logs user
    public String loggin() throws Exception{
        System.err.print("Login user:");

        // Input
        String name = read();

        // Calls rm with name
        int res = rm.login(name);

        if( res == 1 )
        {
            System.out.println("New user Added :"+ name  );
        }

        System.out.println("Logged in as "+ name );
        return name;
    }
    
    // Add a request to the system
    public boolean add( String pname ){
        try
        {
            System.out.println("Getting products...");
            String[] p = rm.get_product(pname);
            
            // No products found
            if ( p == null ){
                // Does not exists 
                System.out.println("Product not found.\nDo you wish to set a request for it?(Y/n)");

                String op = read();

                if( ( op.compareToIgnoreCase("") != 0 ) && ( op.compareToIgnoreCase("y") != 0) )
                {
                    // User says no
                    System.out.println( "Aborting command" );
                }
                else
                {
                    int code = rm.add_product_request(pname);
                    System.out.format("Product added sucssesfuly\nRequest set for %s with code %d\n", pname, code);
 
                }
            }
            else
            {
                if( !p[1].isEmpty() )
                    // Registed and found
                    System.out.format("Product %s found and its located at %s.\n", p[0], p[1]);
                else
                {
                    int code = rm.set_request( pname );
                    System.out.format("Request for %s as ben set with code %d you will be notifyed if someone finds it.\n", pname, code);
                }
            }
 
            // Finish succesfull
            return true;
            
        }
        catch( Exception e )
        {
            e.printStackTrace();
            return false;
        }
    }
    
    // Show requests
    public boolean show(){
        try
        {
            
        }
        catch( Exception e )
        {
            return false;
        }
        
        return true;
    }
    
}
