package so2;

import java.net.*;
import java.io.*;

public class EchoClient {

    private String address= null;
    private int sPort= 0;
    
    public EchoClient(String add, int p) {
	address= add;
	sPort=p;
    }
    
    
    public static void main(String[] args){
	// exigir os argumentos necessarios
	if (args.length < 2) {
	    System.err.println("Argumentos insuficientes:  java EchoClient ADDRESS PORT");
	    System.exit(1);
	}
	
	try {
	    String addr= args[0];
	    int p= Integer.parseInt(args[1]);	
	    
	    EchoClient cl= new EchoClient(addr,p);
	    
	    // ler o texto a enviar ao servidor
	    String s= "mensagem_que_deve_vir_como_argumento";
	    
	    String response = cl.go( s );   // faz o pretendido
            
            System.out.println( response );
            
	}
	catch (Exception e) {
	    System.out.println("Problema no formato dos argumentos");
	    e.printStackTrace();
	}
    }
    
    
    
    public String go(String msg) throws Exception
    {
	Socket socket = new Socket( address, sPort );
        
        OutputStream socketOut = socket.getOutputStream();
        socketOut.write(msg.getBytes());
        
        InputStream socketIn = socket.getInputStream();
        byte[] bytes = new byte[256];
        int size = socketIn.read( bytes );
        return new String(bytes, 0, size);
    }
    
}
