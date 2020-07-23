
import java.util.Vector;

public class Consumidor extends Thread {

    Vector<String> produtos;
    int capacidade = 3;

    public Consumidor(Vector<String> produtos) {
        super();
        this.produtos = produtos;
    }

    public void setCapacidade(int c) {
        this.capacidade = c;
    }


    public void run() {
        String name = Thread.currentThread().getName();
        try {
            System.out.println("# C " + name + " ponto 0");

            for (int i = 0; i < capacidade; i++) { // loop de consumo
                
                 synchronized(produtos){
                    if (produtos.size() > 0) {
                        // *************************************
                        // NAO ALTERAR ESTE BLOCO **************
                        String p = encontraPrimeiroProdutoNovo();
                        int k= produtos.indexOf( p );
                        p= p+"_Usado";
                        Thread.sleep(1000);   // espera propositada para simular ambiente de risco
                        produtos.set(k, p);  // trocar produto novo p usado.
                        // *************************************
                        // *************************************
                    
                        System.out.println("CONSUMIDOR " +name+ " consome "+p);
                    }
                     else {
                        System.out.println("CONSUMIDOR " + name + " interrompido por falta de produto");
                        break;
                    }
                } 
                
                Thread.sleep(1000);
		   	 
	    }  // loop de consumo
	    
	    System.out.println("\t# C " + name + " ponto 1");
	} catch (Exception e) {
	    e.printStackTrace();
	}
    }
    
    
    
    private String encontraPrimeiroProdutoNovo() {
        for (String p: produtos) {
            if (!p.endsWith("_Usado"))
                return p;
        }
        return null; // se não encontra
    }

    
}
