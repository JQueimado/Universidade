package EDA1;

public abstract class Hashtable<T> {
	public HashElement<T>[] tabelaH;
	private int ocupado; 
	
	public Hashtable(){ // construtor sem argumentos
		tabelaH= new HashElement[1009];
	}
	
	public Hashtable(int n){ //construtor com 1 argumento
		tabelaH= new HashElement[n];
	}
	
	public int ocupados(){ //numero de pois�oes ocupadas na hash
		return ocupado;
	}
	
	public float factorCarga(){ //numero de posi�oes ocupadas/tamanho da hash
		return ((float)(ocupado)/tabelaH.length);
	}
	protected abstract int procPos(T s); 
	
	public void alocarTabela(int dim){ // aumentar a tabela
		tabelaH = new HashElement[dim];
	}
	
	
	private static boolean ePrimo(int n){
        if( n == 1 || n % 2 == 0 )
            return false;
        if( n == 2 || n == 3 )
            return true;
        for( int i = 3; i * i <= n; i += 2 )
            if( n % i == 0 )
                return false;
        
        return true;
    }
	
	private static int proxPrimo( int n ){
        if( n % 2 == 0 )
            n++;

        for(int i=0;!ePrimo(n); n += 2 );
        
        return n;
    }
	
	public void tornarVazia(){
		ocupado = 0;
        for(int i = 0; i < tabelaH.length; i++)
        	tabelaH[i] = null;
	}
	
	public T procurar(T o){
		int hash = procPos(o);
		if(tabelaH[hash]==null){
			return null;
		}
		if ((tabelaH[hash].getElemento()).equals(o) && tabelaH[hash].getAtivo() ){
			return o;
		}else{
			return null;
		}
	}
	
	public void remove(T o){
		if (tabelaH[procPos(o)].getElemento().equals(o)){
			tabelaH[procPos(o)].ativo=false;
			ocupado--;
	}
	}
	public void insere (T x){
		int pos = procPos(x);		
		if (tabelaH[pos]!=null && (tabelaH[procPos(x)].getElemento()).equals(x) && tabelaH[procPos(x)].ativo){
		return;
		}
		tabelaH[pos] = new HashElement(x);
		ocupado++;
		if (factorCarga()>=0.5){
			rehash();
		}
	}
	
	public void rehash(){
		HashElement<T>[ ] tabelaAntiga = tabelaH;
		alocarTabela(proxPrimo(2*tabelaH.length));
		for( int i = 0; i < tabelaAntiga.length; i++ ){
			if(tabelaAntiga[i] != null && tabelaAntiga[i].ativo){
				insere(tabelaAntiga[i].elemento);
		}
		}
		}
	
	public String toString(){
		StringBuffer buffer = new StringBuffer();
		
	    buffer.append("[");
	   
	    for (int i = 0; i < this.tabelaH.length; i++) {
	    	buffer.append(System.getProperty("line.separator"));
	    	buffer.append(i+".");
	    	
	    	if (this.tabelaH[i] != null && this.tabelaH[i].ativo==true) {
	    		buffer.append(this.tabelaH[i].toString());
	    		
	    	}
	    }

	    buffer.append("]");
	    return buffer.toString();
	}
	
	public int capacidade(){ //devolve o tamanho da hash
		return tabelaH.length;
	}
	}