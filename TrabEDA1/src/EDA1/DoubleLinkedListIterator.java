package EDA1;

import java.util.NoSuchElementException;

public class DoubleLinkedListIterator<E> implements java.util.Iterator<E> {

	DoubleNode<E> atual;

	public DoubleLinkedListIterator(DoubleNode<E> a){ // metodo com 1 argumento
		atual=a;
	}
	
	public boolean hasNext(){ // verifica se o n� tem um n� seguinte
		return atual.next!=null;
	}
	
	public E next(){
		if (!hasNext()){
			throw new NoSuchElementException("Nao existe proximo elemento");
		}
		E nextItem = atual.elemento;
		atual = atual.next;
		return nextItem;
	}
	
}
