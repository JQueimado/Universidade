package Client;

import java.io.IOException;
import java.util.*;

public class CommandExec {
    
    private RemoteManager rm;
    private String loged_user;
    
    private Properties properties;
    
    private Scanner scanner;
    
    public CommandExec( Scanner scanner , Properties properties ) throws Exception{
        this.rm = new RemoteManager( properties );
        this.scanner = scanner;
        this.properties = properties;
    }
    
    /* AUX methods */
    private String read()throws IOException{
        return this.scanner.nextLine();
    }
    
    /* Commands */
    // Logs user
    public String loggin() throws Exception{
        
        String name = properties.getProperty("def-user");
        
        if( name.compareToIgnoreCase("") == 0 )
        {
            System.err.print("Login user:");
            name = read();
        }

        // Calls rm with name
        int res = rm.login(name);

        if( res == 1 )
        {
            System.out.println("New user Added:"+ name  );
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
                // Does not exist
                System.out.println("Product not found.\nDo you wish to set a request for it? (Y/n)");

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
                    System.out.format("Request for %s as been set with code %d you will be notified if someone finds it.\n", pname, code);
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
            System.out.println("Getting requests");
            String[][] res = rm.get_requests();
            
            if( res == null )
            {
                System.out.println("You have no requests");
                return true;
            }
            
            System.out.format("Your requests:\n|-%10s-|-%10s-|-%s\n", "code", "product", "locasion");
            
            for( int c = 0; c<res[0].length; c++ )
            {
                System.out.format("| %10s | %10s | %s\n", res[0][c], res[1][c], res[2][c]);
            }
            
            System.out.println("Done");
        }
        catch( Exception e )
        {
            e.printStackTrace();
            return false;
        }
        
        return true;
    }
    
    // Sets a product available
    public boolean set( String pname, String locasion ){
        
        System.out.println("Setting product location...");
        rm.set_avalable(pname, locasion);
        System.out.println("Success");
        return true;
    }
    
}
