package Server;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Vector;
import org.postgresql.util.PSQLException;


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
        System.out.println("[..]:Connecting to: "+ uri);
        
        // Create conection
        this.con = DriverManager.getConnection( uri, user, passwd );
        
        // Create Statement
        this.stmnt = con.createStatement();
        
        System.out.println("[OK]:Connection Sucssesfull!");
        
        // Integrity
        try 
        { 
            String query = "Create table usertable( name text primary key );";
            stmnt.executeUpdate(query);
            System.err.println("[OK]:Created 'usertable' plz check if this was ment to happen");
        } 
        catch( PSQLException sqle )
        {
            /* If execption ocures it means the table already exixts */
            System.out.println("[OK]:'usertable' already exixts");
        } 
        
        try 
        { 
            String query = "Create table producttable( product text primary key, loc text );";
            stmnt.executeUpdate(query);
            System.err.println("[OK]:Created 'producttable' plz check if this was ment to happen");
        } 
        catch( PSQLException sqle )
        {
            /* If execption ocures it means the table already exixts */
            System.out.println("[OK]:'producttable' already exixts");
        }
        
        try 
        { 
            String query = "create table requesttable( ident int primary key, product text references producttable(product), name text references usertable(name) );";
            stmnt.executeUpdate(query);
            System.err.println("[OK]:Created 'requesttable' plz check if this was ment to happen");
        } 
        catch( PSQLException sqle )
        {
            /* If execption ocures it means the table already exixts */
            System.out.println("[OK]:'requesttable' already exixts");
        } 
        
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
    
    /* User Database */
    
    // AddUser: Runs a sql insert query on usertable
    public void addUser( String user ) throws Exception{
        try{
            // Define Query
            String query = "insert into usertable values( '" + user + "' );" ;

            //Send Query
            this.stmnt.executeUpdate(query);
        }
        catch( SQLException psqle)
        {
           throw new Exception(" User '"+user+"' already exists" );
       }
    }
    
    // Checks if a user exists 
    public boolean identifyUser( String name ) throws Exception {
        
        // Setup Query
        String query = "Select name from usertable where name = '" + name +"' ;";

        ResultSet resp = stmnt.executeQuery(query);
        
        // if empty no result
        if( !resp.next())
            return false;

        // Imposible but i still check-it it  
        if( !resp.isLast() )
            throw new Exception("Response size invalid");

        if( resp.getString("name").compareTo(name) != 0 )
            throw new Exception("Response invalid");
        
        return true;
        
    }
    
    /* Product Management */
    public void add_product( String name ) throws SQLException{
       
        String query = " insert into producttable values( '"+name+"', '');";
        
        stmnt.executeUpdate(query);
    }
    
    public String[] get_product( String product ) throws SQLException{
        
        String query = "select * from producttable where product='" + product + "';";
        
        ResultSet rs = stmnt.executeQuery(query);
        
        if( !rs.next() )
            return null;
        
        String[] ret = new String[2];
        ret[0] = rs.getString("product");
        ret[1] = rs.getString("loc");
        
        return ret;
    }
    
    /* Request Database */
    public int add_request( String name, String product ) throws Exception{
        
        // Eval user
        String query = "Select name from usertable;";
        ResultSet res = stmnt.executeQuery(query);
        if(! res.next() )
            throw new Exception("unknown user");
        
        // Eval product
        query = "Select product from producttable;";
        res = stmnt.executeQuery(query);
        if(! res.next() )
            throw new Exception("unknown product");
        
        // Add request        
        query = "Select * from requesttable;";
        res = stmnt.executeQuery(query);
        
        int s = 0; 
        while ( res.next() ) s++;
        
        query = "insert into requesttable values("+s+", '"+product+"', '"+name+"' );";
        stmnt.executeUpdate(query);
        
        return s;
        
    }
    
    public ResultSet get_requests( String name ) throws SQLException{
        
        String query = "select ident, product from requesttable natural join producttable;";
        
        return stmnt.executeQuery(query);
        
    }
    
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
