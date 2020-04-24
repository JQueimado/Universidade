package server;

import java.util.Collection;
import java.util.Vector;

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
            DBManager database = new DBManager();
        
            Object[] test = { "joao" };
        
            //System.in.read();
            
            database.add( "usertable", test);
        }
        catch ( Exception e ){
            e.printStackTrace();
            System.out.println( e.getMessage() );
        }
    }
    
}
