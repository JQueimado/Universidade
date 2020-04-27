package Client;

import java.io.*;
import java.util.*;


public class Client {
    
    public static final String prop_file = "client_settings.properties";
    
    public static Properties defaults(File file){
        try
        {
            System.out.println("[..]: Creating default properties");
            
            file.createNewFile();
            OutputStream out = new FileOutputStream(file);
            
            Properties prop = new Properties();
            
            // Default properties
            prop.setProperty("def-reghost", "localhost");
            prop.setProperty("def-regport", "1099");
            prop.setProperty("def-user", "");
            prop.setProperty("storage-filename", "Storage.dataobj");
            
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
                System.err.println("[OK]: File "+prop_file+" not found");
                prop = defaults(temp);
            }
            else
            {
                System.out.println("[..]:Loading properties");
                
                InputStream is = new FileInputStream(temp);
                prop = new Properties();
                prop.load(is);
                
                System.out.println("[OK]:Properties Loaded Successfully");
            }
            
            return prop;
            
        }
        catch(Exception e){
            System.err.println("[ER]:Could not load or set properties");
            e.printStackTrace();
            return null;
        }
    }
    
    /********** MAIN *************/
    public static void main(String[] args) throws Exception {
        
        try
        {
            Scanner scanner = new Scanner(System.in);
            Properties properties = get_props();
            if( Boolean.parseBoolean( properties.getProperty("properties-reset") ) )
            {
                System.out.println("[..]:Resetting Properties");
                File nf = new File(prop_file);
                nf.delete();
                properties = defaults(nf);
            }
            
            CommandExec cmd = new CommandExec( scanner, properties );
            
            String name = cmd.loggin();
            
            while( true )
            {
                System.out.print( name + " >>");
                
                String[] a = scanner.nextLine().split(" ");
                
                // Add
                if( a[0].compareToIgnoreCase("add") == 0 )
                {
                    cmd.add(a[1]);
                }
                // Show
                else if ( a[0].compareToIgnoreCase("show") == 0 )
                {
                    cmd.show();
                }
                // Set
                else if ( a[0].compareToIgnoreCase("set") == 0 )
                {
                    cmd.set(a[1], a[2]);
                }
                // Exit
                else if ( a[0].compareToIgnoreCase("exit") == 0 )
                {
                    System.out.println("Quiting...");
                    return;
                }
                else if ( a[0].compareToIgnoreCase("mstorage") == 0 )
                {
                    cmd.mstorage();
                }
                else
                {
                    System.err.println("[ER]:Command not found");
                }
            }
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        
    }
}
