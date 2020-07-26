package EDA1;

public class NoArv<T> {
	T elemento;
	NoArv esquerdo;
	NoArv direito;

	public NoArv(T elemento) { // metodo com 1 argumento
		this(elemento, null, null);
	}

	public NoArv(T o, NoArv<T> esq, NoArv<T> dir) {
		elemento = o;
		esquerdo = esq;
		direito = dir;
	}
	public String toString(){
		return (String) elemento;
	}

}
