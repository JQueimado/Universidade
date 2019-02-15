package EDA1;

public class ArrayQueue<E> implements Queue<E>{
	E[]lista;
	int inicio;
	int fim;
	
	@SuppressWarnings("unchecked")
	public ArrayQueue(){
		lista= (E[]) new Object[10];
		inicio=0;
		fim=0;
	}
	 
	@SuppressWarnings("unchecked")
	public ArrayQueue(int n){
		lista= (E[]) new Object[n];
		inicio=0;
		fim=0;
	}
	
	
	public void enqueue(E o){
		if (size()==lista.length)
				 throw new OverflowQueueException("Full");
		
			lista[fim]=o;
			fim=inc(fim);
		}
	

	public E front() {
		return lista[inicio];
	}

	public E dequeue() {
		 if (empty())
			 throw new EmptyStackException("Empty");
		
		 
		 E x=lista[inicio];
		 lista[inicio]=null;
		 inicio=inc(inicio);
		 return x;
		 }

	public int size() {
		return(lista.length-inicio+fim) % lista.length;
		
	}

	public boolean empty() {
		return inicio==fim;
	}

	private int inc(int i){
		return (i+1)%lista.length;
	}
	public String toString(){
		String s= "[ ";
		for (int i=0; i<lista.length; i++){
			s+=lista[i]+ " ";
		}
		return s+"]";
	}
}
