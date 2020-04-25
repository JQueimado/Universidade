package Client;

import Remotes.LoginAgent;

public class Client {
    public static void main(String[] args) throws Exception {
        
        try
        {
            RemoteManager rm = new RemoteManager();
            
            /* Login User */
            System.err.print("Login user:");
            
            // Input
            byte[] rawinput = new byte[20];
            
            int s = System.in.read(rawinput);
            
            String name = new String(rawinput);
            name = name.substring(0,s-1);
            
            // Calls rm with name
            int res = rm.login(name);
            
            if( res == 1 ){
                System.out.println("New user Added :"+ name  );
            }
            
            System.out.println("Logged in as "+ name );
            
            
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        
    }
}
