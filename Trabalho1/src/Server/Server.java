package Server;

import Remotes.LoginAgent;

/*
    Class Server
*/ 
public class Server {

    /*
        Program Main
    */
    public static void main(String[] args) {
        
        try
        {
            // Start Database Manager
            DBManager database = new DBManager();
            
            // Strat RemoteObject Manager
            RMIController remote_obj_mngr = new RMIController();
            
            // Start Remote objects
            System.out.println("[..]:Creating Remote instances");
            
            LoginAgent logobj = new LoginAgentImp( database );
            
            System.out.println("[OK]:All instances created sucsesfully");
            
            // Add Objects to manager
            System.out.println("[..]:Linking Remote objects to the controller");
           
            remote_obj_mngr.addRemoteObject(logobj, "loguser");
            
            System.out.println("[OK]:Linked Sucsesfull");
            
            System.out.println("-- Server Start --");
            
            
        }
        catch ( Exception e ){
            e.printStackTrace();
            System.out.println( e.getMessage() );
        }
    }
    
}
