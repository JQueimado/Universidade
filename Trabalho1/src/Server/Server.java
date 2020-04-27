package Server;

import Remotes.LoginAgent;
import Remotes.ProductAgent;
import Remotes.RequestAgent;

/*
    Class Server
*/ 
public class Server {

    /*
        Main Program
    */
    public static void main(String[] args) {
        
        try
        {
            // Start Database Manager
            DBManager database = new DBManager();
            
            // Start RemoteObject Manager
            RMIController rmic = new RMIController();
            
            // Start Remote objects
            System.out.println("[..]:Creating Remote instances");
            
            LoginAgent   la = new LoginAgentImp  ( database );
            RequestAgent ra = new RequestAgentImp( database );
            ProductAgent pa = new ProductAgentImp( database );
            
            System.out.println("[OK]:All instances created successfully");
            
            // Add Objects to manager
            System.out.println("[..]:Linking Remote objects to the controller");
           
            rmic.addRemoteObject(la, "loguser");
            rmic.addRemoteObject(ra, "requestagent");
            rmic.addRemoteObject(pa, "productagent");
            
            System.out.println("[OK]:Linked Successfull");
            
            System.out.println("-- Server Start --");
            
        }
        catch ( Exception e ){
            e.printStackTrace();
            System.out.println( e.getMessage() );
        }
    }
    
}
