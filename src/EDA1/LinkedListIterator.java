package EDA1;

import java.util.NoSuchElementException;

public class LinkedListIterator<E> implements java.util.Iterator<E> {

	SingleNode<E> atual; // n� atual
	
	public LinkedListIterator(SingleNode<E> a){ // metodo com 1 argumento
		atual=a;
	}
	
	public boolean hasNext(){ // verifica se o n� tem um n� seguinte
		return atual.next!=null;
	}
	
	public E next(){ // coloca o n�, no n� a seguir
		if (!hasNext()){
			throw new NoSuchElementException("Nao existe proximo elemento");
		}
		E nextItem = atual.element; //um elemento fica no n� atual
		atual = atual.next;
		return nextItem;
	}
	
}
