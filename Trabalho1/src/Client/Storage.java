package Client;

import java.io.*;

class Data implements Serializable{
    public String[] sent_data;
    public String[] recv_data;
    public String[][] aux_recv_data;
}

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
            
            Data temp = new Data();
            temp.recv_data = new String[0];
            temp.sent_data = new String[0];
            temp.aux_recv_data = new String[0][0];
            this.out.writeObject(temp);
            
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
            Data temp = (Data) this.in.readObject();
            temp.sent_data = data;
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
            Data temp = (Data) this.in.readObject();
            temp.recv_data = data;
            temp.aux_recv_data = new String[0][0];
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
            Data temp = (Data) this.in.readObject();
            temp.recv_data = data;
            temp.aux_recv_data = aux_data;
            this.out.writeObject(temp);
            
        }
        catch( Exception e )
        {
            System.out.println("[ER]:Error storing receaved storage");
            e.printStackTrace();
        }
    } 
    
}
