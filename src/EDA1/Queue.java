package EDA1;

public interface Queue<E> {
	 public void enqueue(E o);
	 public E front();
	 public E dequeue();
	 public int size();
	 public boolean empty(); 
	 public String toString();
}
 