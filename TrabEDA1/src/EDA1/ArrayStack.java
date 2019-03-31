package EDA1;

import java.util.EmptyStackException;


public class ArrayStack <E> implements Stack<E> {
	E[] lista;
	int top=0;
	public static final int capacity = 100;
	
	public ArrayStack(int cap){
		lista= (E[]) new Object[capacity];
	}
	
	public ArrayStack(){
		this(capacity);
	}
	
	public void push(E o) {
		if (top==10){
			throw new ArrayIndexOutOfBoundsException();
		}
		lista[top]=o;
		top++;
	}
 
	public E top() {
		return lista[top-1];
	}

	public E pop() {
		if (top==0){
			throw new EmptyStackException();
		}
		top--;
		E temporario=lista [top];
		return temporario;
		
	}

	public int size() {
		return top;
	}

	public boolean empty() {
		return top==0;
	}
	public String toString (){
		System.out.print("[ ");
		for (int i=0; i<top; i++){
			System.out.print(lista[i]+ " ");
		}
		System.out.print("]");
		return "";
	}
}
