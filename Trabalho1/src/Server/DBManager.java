package Server;

import java.sql.*;
import java.util.*;
import org.postgresql.util.PSQLException;


public class DBManager {

    /* Class Variables */
    private Connection con;
    private Statement stmnt;
    
    private String usertable;
    private String producttable;
    private String requesttable;
    //*****************
    
    /* Constructors */
    
    //Normal call no default parameters
    public DBManager( String user, String passwd, String database, String host, int port, Properties properties ) throws Exception{
        Class.forName("org.postgresql.Driver");
        
        this.usertable = properties.getProperty("table-user");
        this.requesttable = properties.getProperty("table-request");
        this.producttable = properties.getProperty("table-product");
        
        // Setup database uri
        String uri = "jdbc:postgresql://"+host+":"+port+"/"+database;
        System.out.println("[..]:Connecting to: "+ uri);
        
        // Create conection
        this.con = DriverManager.getConnection( uri, user, passwd );
        
        // Create Statement
        this.stmnt = con.createStatement();
        
        System.out.println("[OK]:Connection Successful!");
        
        // Integrity
        try 
        { 
            String query = "Create table "+ this.usertable +"( name text primary key );";
            stmnt.executeUpdate(query);
            System.err.println("[OK]:Created '"+ this.usertable +"' plz check if this was meant to happen");
        } 
        catch( PSQLException sqle )
        {
            /* If execption occures it means the table already exists */
            System.out.println("[OK]:'"+ this.usertable +"' already exists");

        } 
        
        try 
        { 
            String query = "Create table "+ this.producttable +"( product text primary key, loc text );";
            stmnt.executeUpdate(query);
            System.err.println("[OK]:Created '"+ this.producttable +"' plz check if this was meant to happen");
        } 
        catch( PSQLException sqle )
        {
            /* If exeception ocures it means the table already exists */
            System.out.println("[OK]:'"+ this.producttable +"' already exists");
        }
        
        try 
        { 
            String query = "create table "+this.requesttable+"( ident int primary key, product text references producttable(product), name text references usertable(name) );";
            stmnt.executeUpdate(query);
            System.err.println("[OK]:Created '"+this.requesttable+"' plz check if this was meant to happen");
        } 
        catch( PSQLException sqle )
        {
            /* If exeception occures it means the table already exists */
            System.out.println("[OK]:'"+this.requesttable+"' already exists");
        } 
        
    }
    
    //Port omition results in the default postgress port (5432)
    public DBManager( String user, String passwd, String database, String host, Properties properties) throws Exception{
        this(user, passwd, database, host, 5432, properties);
    }
    
    //Host omition results in the default host (localhost)
    public DBManager( String user, String passwd, String database, Properties properties) throws Exception{
        this(   user, 
                passwd, 
                database, 
                properties.getProperty("db-host"),
                Integer.parseInt( properties.getProperty("db-port") ),
                properties);
    }
    
    //parameter omition uses default values (localhost)
    public DBManager( Properties properties ) throws Exception{
        this(   properties.getProperty("db-user"), 
                properties.getProperty("db-paswd"), 
                properties.getProperty("db-database"), 
                properties.getProperty("db-host"),
                Integer.parseInt( properties.getProperty("db-port") ),
                properties);
    }
    
    //*****************
    
    /* Methods */
    
    /* User Database */
    
    // AddUser: Runs a sql insert query on usertable
    public void addUser( String user ) throws Exception{
        try{
            // Define Query
            String query = "insert into "+ this.usertable +" values( '" + user + "' );" ;

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
        String query = "Select name from "+ this.usertable +" where name = '" + name +"' ;";

        ResultSet resp = stmnt.executeQuery(query);
        
        // if empty no result
        if( !resp.next())
            return false;

        // Impossible but i still check it  
        if( !resp.isLast() )
            throw new Exception("Response size invalid");

        if( resp.getString("name").compareTo(name) != 0 )
            throw new Exception("Response invalid");
        
        return true;
        
    }
    
    /* Product Management */
    public void add_product( String name ) throws SQLException{
       
        String query = " insert into "+ this.producttable +" values( '"+name+"', '');";
        
        stmnt.executeUpdate(query);
    }
    
    public String[] get_product( String product ) throws SQLException{
        
        String query = "select * from "+ this.producttable +" where product='" + product + "';";
        
        ResultSet rs = stmnt.executeQuery(query);
        
        if( !rs.next() )
            return null;
        
        String[] ret = new String[2];
        ret[0] = rs.getString("product");
        ret[1] = rs.getString("loc");
        
        return ret;
    }
    
    public void set_available(String product, String local) throws SQLException{
        
        String query = "update "+ this.producttable +" set loc='"+local+"' where product='"+product+"';";
        
        stmnt.executeUpdate(query);
        
    }
    
    /* Request Database */
    public int add_request( String name, String product ) throws Exception{
        
        // Eval user
        String query = "Select name from "+this.usertable+" where name='"+name+"';";
        ResultSet res = stmnt.executeQuery(query);
        if(! res.next() )
            throw new Exception("unknown user");
        
        // Eval product
        query = "Select product from "+ this.producttable +" where product='"+product+"';";
        res = stmnt.executeQuery(query);
        if(! res.next() )
            throw new Exception("unknown product");
        
        // Add request        
        query = "Select * from "+this.requesttable+";";
        res = stmnt.executeQuery(query);
        
        int s = 0; 
        while ( res.next() ) s++;
        
        query = "insert into "+this.requesttable+" values("+s+", '"+product+"', '"+name+"' );";
        stmnt.executeUpdate(query);
        
        return s;
        
    }
    
    public String[][] get_requests( String name ) throws SQLException{
        
        String query = "select ident, product, loc from "+this.requesttable+" natural join "+ this.producttable +" where name='"+name+"';";
        ResultSet res = stmnt.executeQuery(query);
        
        List<String> ident = new ArrayList();
        List<String> products = new ArrayList();
        List<String> locasions = new ArrayList();
        
        while(res.next())
        {
            ident.add( String.valueOf( res.getInt("ident") ) );
            products.add( res.getString("product") );
            locasions.add( res.getString("loc") );
        }
        
        String[][] ret = new String[3][ident.size()];
        
        String[] identr = new String[ident.size()];
        ret[0] = ident.toArray(identr);
        
        String[] prodr = new String[products.size()];
        ret[1] = products.toArray(prodr);
        
        String[] locsr = new String[locasions.size()];
        ret[2] = locasions.toArray(locsr);
        
        return ret;
        
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
