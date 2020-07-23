import java.util.Vector;



public class Aplicacao {


    static Vector<String> produtos;


    public static void main(String[] args) throws Exception {
	System.out.println("main: inicio ---------------------------");
	
	produtos= new Vector<String>();   // partilhada entre as threads
	

	// 3 objectos do tipo Thread (subclasse Consumidor)
	Consumidor c1= new Consumidor(produtos);
	Consumidor c2= new Consumidor(produtos);
	Consumidor c3= new Consumidor(produtos);
	
	// 1 produtor
	Produtor p1= new Produtor(produtos);

	// lancar as 3+1, cada uma executara por si
        p1.start();
                
	c1.start();
	c2.start();
	c3.start();
	
	System.out.println("main: fim ---------------------------");
	
    }
    
}
