package EDA1;

public class ArvoreBinaria <E extends Comparable<E>> {
	public E n; 
	NoArv<E> raiz; 
	
	public ArvoreBinaria(){
		raiz=null;
	}
	public boolean isEmpty(){
		return raiz==null;
	}
	public void makeEmpty(){
		raiz=null;
	}
	public  boolean isLeaf(NoArv<E> z){
		return z.esquerdo==null && z.direito==null;
	}
	public boolean contem(E o){ 
		return contem(o,raiz);
	}
	public boolean contem(E o, NoArv<E> x){
		if (x==null){
			return false;
		}else{
			if (x.elemento.compareTo(o)<0){
				return contem(o,x.esquerdo); 
			}else{
				if (x.elemento.compareTo(o)>0){
					return contem(o,x.direito);
				}else{
					return true;
					}
				}
			}
		}
	public E findMenor(){ 
		if (raiz==null){
			return null;
		}else{
			return findMenor(raiz);
		}
	}
	public E findMenor(NoArv<E> m){
		if (m.esquerdo==null){
			return m.elemento;
		}else{
			return (E) findMenor(m.esquerdo);
		}
	}
	
	public E findMaior(){
		if (raiz==null){
			return null;
		}else{
			return findMaior(raiz);
		}
	}
	
	public E findMaior (NoArv<E> m){
		if (m.direito==null){
			return m.elemento;
		}else{
			return (E) findMaior (m.direito);
		}
	}
	
	public void insere (E x){ 
		raiz=insere(x,raiz);
	}
	
	public NoArv<E> insere(E x, NoArv<E> m){
		if(m==null){
			m=new NoArv<E> (x, null,null);
		}else{
			if (m.elemento.compareTo(x)>0){ 
				m.esquerdo=insere(x,m.esquerdo);
			}else{
				if (m.elemento.compareTo(x)<0){
					m.direito=insere (x,m.direito);
				}
			} 
		}
		return m;
	}
	
	public void remove (E o){
		raiz=remove(o,raiz);
	}
	private NoArv<E> remove(E o, NoArv<E> m){
		if (m==null){
			return m;
		}
		if(m.elemento.compareTo(o)<0){ 
			m.direito=remove(o,m.direito);
		}
		else{
			if(m.elemento.compareTo(o)>0){
				m.esquerdo=remove(o,m.esquerdo);
			}
			else{
				if(m.esquerdo!=null && m.direito!=null){
					E min=(E) findMenor(m.direito);
					m.elemento=min;
					m.direito=remove(min,m.direito);
				}
				else{
					if(m.esquerdo==null){
						m=m.direito;
					}
				
					else{
						m=m.esquerdo;
						}
					}
			}
		}
					return m;
			
	}
	
public void printTree(NoArv<E> m){
		if(m!=null){
			printTree(m.esquerdo);
			System.out.println(m.elemento);
			printTree(m.direito);
		}
	}
}
