package EDA1;

public class SingleNode <T>{

	T element;
	SingleNode <T> next;
	
	public SingleNode (T o){
		element=o;
		next=null;
	}
	public SingleNode(){
		this(null);
	}
	public T getElement(){
		return element;
	}
	public SingleNode(T e, SingleNode<T> n){
		 element=e;
		 next=n;
	}
	public void setElement (T o){
		element=o;
	}
	public SingleNode<T> getNext(){
		return next;
	}
	public void setNext (SingleNode<T> n){
		next=n;
	}
}
