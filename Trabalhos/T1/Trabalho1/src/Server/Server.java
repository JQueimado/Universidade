package Server;

import Remotes.LoginAgent;
import Remotes.ProductAgent;
import Remotes.RequestAgent;
import java.io.*;
import java.util.Properties;

/*
    Class Server
*/ 
public class Server {

    /*
        Main Program
    */
    
    public static final String prop_file = "server_settings.properties";
            
    public static Properties defaults(File file){
        try
        {
            System.out.println("[..]:Creating default properties");
            
            file.createNewFile();
            OutputStream out = new FileOutputStream(file);
            
            Properties prop = new Properties();
            
            // Default properties
            prop.setProperty("def-reghost", "localhost");
            prop.setProperty("def-regport", "1099");
            
            prop.setProperty("db-host", "localhost");
            prop.setProperty("db-port", "5432");
            prop.setProperty("db-database", "trab");
            prop.setProperty("db-user", "user1");
            prop.setProperty("db-paswd", "1234");
            
            prop.setProperty("table-user", "usertable");
            prop.setProperty("table-request", "requesttable");
            prop.setProperty("table-product", "producttable");
            
            prop.setProperty("name-log", "loguser");
            prop.setProperty("name-request", "requestagent");
            prop.setProperty("name-product", "productagent");
            
            prop.setProperty("properties-reset", "false");
            
            prop.store(out, null);
            
            System.out.println("[OK]:Default properties set");
            return prop;
        }
        catch(Exception e)
        {
            System.err.println("[ER]:Error Creating properties");
            e.printStackTrace();
            return null;
        }
    }
    
    public static Properties get_props(){
        try
        {
            File temp = new File(prop_file);
            Properties prop;
            
            if (! temp.exists() )
            {
                System.err.println("[OK]:File "+prop_file+" not found");
                prop = defaults(temp);
            }
            else
            {
                System.out.println("[..]:Loading properties");
                
                InputStream is = new FileInputStream(temp);
                prop = new Properties();
                prop.load(is);
                
                System.out.println("[OK]:Properties Loaded Sucsessfuly");
            }
            
            return prop;
            
        }
        catch(Exception e){
            System.err.println("[ER]:Could not load or set properties");
            e.printStackTrace();
            return null;
        }
    }
    
    public static void main(String[] args) {
        
        try
        {
            Properties properties = get_props();
            if( Boolean.parseBoolean( properties.getProperty("properties-reset") ) )
            {
                System.out.println("[..]:Reseting Properties");
                File nf = new File(prop_file);
                nf.delete();
                properties = defaults(nf);
                System.out.println("[OK]:Properties Reset");
            }
            
            // Start Database Manager
            DBManager database = new DBManager( properties );
            
            // Strat RemoteObject Manager
            RMIController rmic = new RMIController( properties );
            
            // Start Remote objects
            System.out.println("[..]:Creating Remote instances");
            
            LoginAgent   la = new LoginAgentImp  ( database );
            RequestAgent ra = new RequestAgentImp( database );
            ProductAgent pa = new ProductAgentImp( database );
            
            System.out.println("[OK]:All instances created successfully");
            
            // Add Objects to manager
            System.out.println("[..]:Linking Remote objects to the controller");
           
            rmic.addRemoteObject(la, properties.getProperty("name-log"));
            rmic.addRemoteObject(ra, properties.getProperty("name-request"));
            rmic.addRemoteObject(pa, properties.getProperty("name-product"));
            
            System.out.println("[OK]:Linked Successfull");
            
            System.out.println("-- Server Start --");
            
        }
        catch ( Exception e ){
            e.printStackTrace();
            System.out.println( e.getMessage() );
        }
    }
    
}
