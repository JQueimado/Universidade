package EDA1;

public class DoubleLinkedList <T> implements Iterable<T> {

	private DoubleNode <T> Header;
	private DoubleNode <T> Footer;
	private int size;

	public DoubleLinkedList(){
		Header = new DoubleNode<T>();
		Footer = new DoubleNode<T>();
		Header.next=Footer;
		Footer.prev=Header;
		size = 0;

	}
	public java.util.Iterator<T> iterator(){
		return new DoubleLinkedListIterator<>(Header.next);
	}

	public void add(T content){
		DoubleNode <T>a = new DoubleNode<T> (content,null,null);
		a.prev=Footer.prev;
		Footer.prev=a;
		a.next=Footer;
		a.prev.next=a;
		size++;

	}
	public void add(int i, T content){
		if (i>=0){
			DoubleNode<T> node = Header.next;
			for (int a=0;a<i;a++){

				node = node.next;

			}
			DoubleNode<T> addnode = new DoubleNode<T>(content,null,null);

			addnode.prev=node.prev;
			addnode.next=node;
			node.prev.next=addnode;
			node.prev=addnode;
			size++;
		}
	}
	public String toString(){
		DoubleNode<T> node = Header.next;
		String list = "[";
		while (node!=Footer){
			list+=node.elemento;
			node=node.next;
			if (node != Footer){
				list+=";";
			}
		}
		return list+"]";
	}
	public DoubleNode<T> remove(int i){
		DoubleNode<T> node = Header;
		if(size>i && i>=0){
			for (int a=0; a<=i;a++){
				node = node.next;
			}
			node.next.prev=node.prev;
			node.prev.next=node.next;
		}
		size--;
		return node;
	}
	public int size(){
		return size;
	}
	public DoubleNode<T>getFooter(){
		return Footer;
	}
	public T getElement(int i){
		DoubleNode<T> base = Header;
		if(i>=0 && i<size ){
			for (int a = 0; a<=i; a++){
				base = base.next;
			}
			return base.elemento;
		}
		else{
			return null;
		}
	}

	public void set(int a, T x) { // altera um valor na posi�ao pretendida
		if (a > size) {
			return;
		}

		DoubleNode<T> n = new DoubleNode<T>(x);
		DoubleNode<T> noit = Header;

		for (int i = 0; i < a + 1; i++) {
			noit = noit.next;
		}

		noit.elemento = n.elemento;
	}
}