package so2;

import java.net.*;
import java.io.*;

public class EchoServer {

    private int serverPort;	
    
    public EchoServer(int p) {
	serverPort= p;		
    }
    
    
    public static void main(String[] args){
	System.err.println("SERVER...");
	if (args.length<1) 
        {
	    System.err.println("Missing parameter: port number");	
	    System.exit(1);
	}
	int p=0;
	try 
        {
	    p= Integer.parseInt( args[0] );
            
            EchoServer serv= new EchoServer(p);
            serv.servico(); 
	
        }
	catch (Exception e) {
	    e.printStackTrace();
	    System.exit(2);
	}
        
    }

    
    // activa o servidor no porto indicado em "serverPort"
    public void servico() throws Exception {
	
	ServerSocket sSocket = new ServerSocket( serverPort );

        Socket cSocket = sSocket.accept();
        
        InputStream inFromSocket = cSocket.getInputStream();
        OutputStream outToSocket = cSocket.getOutputStream();
        
        byte[] bytes = new byte[256];
        
        int size = inFromSocket.read(bytes);
        
        String msg = new String( bytes, 0, size );
        
        msg = "os2_[" + msg +"]_so2";
        
        System.out.println( msg );
        
        outToSocket.write( msg.getBytes() );
        
        

    }


}
