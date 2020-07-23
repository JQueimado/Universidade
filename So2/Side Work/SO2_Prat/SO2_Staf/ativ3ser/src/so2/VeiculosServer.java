package so2;

import java.io.*;
import java.net.*;
import java.util.Vector;

public class VeiculosServer {
    private int serverPort;	
    
    private Vector<Registo> repositorio;
    
    public VeiculosServer(int p) {
	serverPort= p;		
	repositorio= new Vector(); // INICIALIZE o Vector
    }
    

    
    public static void main(String[] args){
	System.err.println("SERVER...");
	if (args.length<1) {
		System.err.println("Missing parameter: port number");	
		System.exit(1);
	}
	int p=0;
	try {
	    p= Integer.parseInt( args[0] );
	}
	catch (Exception e) {
		e.printStackTrace();
		System.exit(2);
	}
	
	
	VeiculosServer serv= new VeiculosServer(p);
        serv.servico();   // activa o servico
    }

    public void servico() {

	try {

	    ServerSocket sSocket = new ServerSocket(serverPort);
	  
	    while (true) {
		Socket cSocket = sSocket.accept();
		
		try {
		    Object objPedido= null;
		    // le os dados do pedido, como um OBJECTO "objPedido"		
                    ObjectInputStream inFromClient = new ObjectInputStream( cSocket.getInputStream() );
                    
                    objPedido = inFromClient.read();

		    
		    // apreciar o objecto com o pedido recebido:
		    if (objPedido==null)
			System.err.println("PEDIDO NULL: esqueceu-se de alguma coisa");
		    
		    if (objPedido instanceof PedidoDeConsulta) {
			PedidoDeConsulta pc= (PedidoDeConsulta) objPedido;
			
			// procurar o registo associado a matricula pretendida
                        String matricula = pc.getMatricula();

			// pesquisar no servidor (Vector, mais tarde num ficheiro)
                        Registo resposta = null;
                        
                        for (Registo r : repositorio){
                            if( r.getMatricula().equals(pc.getMatricula()) ){
                                resposta = r;
                                break;
                            }
                        }
			
			// enviar objecto Cliente via socket
                        ObjectOutputStream outToClient = new ObjectOutputStream(cSocket.getOutputStream());
                                
			// se encontra devolve o registo, se não, devolve um novo objecto ou string a representar que nao encontrou
                        outToClient.writeObject(resposta);
			
		    }
		    else if (objPedido instanceof PedidoDeRegisto) {
			PedidoDeRegisto pr= (PedidoDeRegisto) objPedido; // ...


			// ver se ja existia registo desta matricula
                        Registo search = null;
                        
                        for (Registo r : repositorio){
                            if( r.getMatricula().equals(pr.getRegisto().getMatricula()) ){
                                search = r;
                                break;
                            }
                        }
                        
                        ObjectOutputStream outToClient = new ObjectOutputStream(cSocket.getOutputStream());
                        
                        if ( search == null )
                            outToClient.write("ERRO:Registo Existente".getBytes());
                        else{
                            repositorio.add(pr.getRegisto());
                        }
			
			// adicionar ao rep local (se nao e' uma repeticao)

			
			// responder ao cliente


		    }
		    else
			System.out.println("PROBLEMA");
		    
                }
                catch (Exception exNoAtendimento) {
                    exNoAtendimento.printStackTrace();
                }
                finally {  // fechar o socket de dados
                    // fechar o socket de dados dedicado a este cliente:
                    try {
                        //AQUI: fechar o socket de dados
                    }
                    catch (Exception e002) {
                    }
                }
                
		
	    
		
	    }  // ... ciclo de atendimento
	
	}
	catch (Exception problemaBindAccept) {
	    problemaBindAccept.printStackTrace();
	}

    }


}
