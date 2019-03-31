package EDA1;

public class LinHashTable<T> extends Hashtable<T>{

	public LinHashTable(){ //construtor vazio
		super();
	}
	
	public LinHashTable(int tamanho) { //construtor com 1 argumento
		super(tamanho);
	}
	
	protected int procPos(T s) {
		int m=Math.abs(s.hashCode())% tabelaH.length;
		if (tabelaH[m]==null){
			return m;
		}
		
		else{
			while(tabelaH[m]!=null){
				if ((tabelaH[m].getElemento()).equals(s)){
					return m;
				}
				if (tabelaH[m].ativo==false){
					return m;
				}
				if (m==tabelaH.length){
					m=0;
				}
				m++;
			}
		}
		return m;
	}
}