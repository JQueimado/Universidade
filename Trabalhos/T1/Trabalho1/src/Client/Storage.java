package Client;

import java.io.*;

public class Storage {
    
    private ObjectOutputStream out;
    private ObjectInputStream in;
    
    public Storage( String fname ){
        try
        {
            System.out.println("[..]:Setting local storage");
            File f = new File(fname);
            if( !f.exists() )
                f.createNewFile();
            
            this.out = new ObjectOutputStream(new FileOutputStream(f));
            this.in = new ObjectInputStream(new FileInputStream(f));
            
            Object[] data = new Object[3];
            data[0] = new String[0];
            data[1] = new String[0];
            data[2] = new String[0][0];
            this.out.writeObject(data);
            
            System.out.println("[OK]:Storage set at "+ fname );
            
        }
        catch( Exception e )
        {
            System.err.println("[ER]:Error seting local storage");
            e.printStackTrace();
        }
    }
    
    // Store mesage sent
    public void store_send_msg( String[] data ){
        try
        {
            Object[] temp = (Object[]) this.in.readObject();
            temp[0] = data;
            this.out.writeObject(temp);
        }
        catch( Exception e )
        {
            System.out.println("[ER]:Error storing sent storage");
            e.printStackTrace();
        }
    }
    
    // Store mesage receaved
    public void store_recv_msg( String[] data ){
        try
        {
            Object[] temp = (Object[]) this.in.readObject();
            temp[0] = data;
            temp[1] = new String[0][0];
            this.out.writeObject(temp);
        }
        catch( Exception e )
        {
            System.out.println("[ER]:Error storing receaved storage");
            e.printStackTrace();
        }
    } 
    
    // Store mesage receaved with aux_data
    public void store_recv_msg( String[] data, String[][] aux_data ){
        try
        {
            Object[] temp = (Object[]) this.in.readObject();
            temp[0] = data;
            temp[1]= aux_data;
            this.out.writeObject(temp);
            
        }
        catch( Exception e )
        {
            System.out.println("[ER]:Error storing receaved storage");
            e.printStackTrace();
        }
    } 
    
    public void show(){
        try
        {
            Object[] data = (Object[]) this.in.readObject();

            System.out.println("Last sent mesage: ");
            System.out.println( data[0] );
            
            System.out.println("Last received mesage: ");
            System.out.println( data[1] );
            
            System.out.println("Aux data to recive:");
            System.out.println( data[2] );
            
        }
        catch( Exception e )
        {
            System.out.println("[ER]:Error reading storage");
            e.printStackTrace();
        }
    }
}
