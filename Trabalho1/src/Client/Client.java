package Client;

import java.util.Scanner;

public class Client {
    
    public static void main(String[] args) throws Exception {
        
        try
        {
            Scanner scanner = new Scanner(System.in);
            CommandExec cmd = new CommandExec( scanner );
            
            String name = cmd.loggin();
            
            while( true )
            {
                System.out.print( name + " >>");
                
                String[] a = scanner.nextLine().split(" ");
                
                if( a[0].compareTo("add") == 0 )
                {
                    cmd.add(a[1]);
                }
            }
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        
    }
}
