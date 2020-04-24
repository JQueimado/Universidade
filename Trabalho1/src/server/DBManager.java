
package server;

import java.sql.*;
import java.util.Vector;


public class DBManager {

    /* Class Variables */
    private Connection con;
    private Statement stmnt;
    
    //*****************
    
    /* Constructors */
    
    //Normal call no default parametrers
    public DBManager( String user, String passwd, String database, String host, int port ) throws Exception{
        Class.forName("org.postgresql.Driver");
        
        // Setup database uri
        String uri = "jdbc:postgresql://" +host+":"+ port+"/"+database;
        System.out.println("Connecting to: "+ uri);
        
        // Create conection
        this.con = DriverManager.getConnection( uri, user, passwd );
        
        // Create Statement
        this.stmnt = con.createStatement();
        
        System.out.println("Connection Sucssesfull!");
        
    }
    
    //Port omition results in the default postgress port (5432)
    public DBManager( String user, String passwd, String database, String host) throws Exception{
        this(user, passwd, database, host, 5432);
    }
    
    //Host omition results in the default host (localhost)
    public DBManager( String user, String passwd, String database) throws Exception{
        this(user, passwd, database, "localhost", 5432);
    }
    
    //parameter omition uses default values (localhost)
    public DBManager() throws Exception{
        this("user1", "1234", "trab", "localhost", 5432);
    }
    
    //*****************
    
    /* Methods */
    // Add: Runs a sql insert query
    public void add( String table, Object[] values ) throws Exception{
        
        String query = "insert into "+ table +" values(";
       
        // Generate quary
        
        // Code subject to changes
        for ( Object v: values )
        {
            Class vClass = v.getClass();
            
            if (vClass == String.class)
            {
                query += "'" + (String) v +"'";
            }
            else if ( vClass == Integer.class )
            {
                query += (Integer) v;
            }
            else
                throw new Exception( "Unsuported Object type" );
            
            query+=",";
        }
        
        query = query.substring(0,query.length()-1) + ");";
        
        System.out.println(query);
        
        //Send Query
        this.stmnt.executeUpdate(query);
    }
    
    public ResultSet get( String table )
    
    // Close: closes the connection to the database
    public void close() throws Exception {
        this.stmnt.close();
        this.con.close();
    }
    
    //Finalizer (just in case)
    @Override
    public void finalize() {
        try 
        {
            this.close();
        } 
        catch (Exception e) 
        {
            e.printStackTrace();
        }
    }
    
}
