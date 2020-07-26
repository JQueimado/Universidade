package EDA1;

public class AVLIteratorPostOrder<T> implements java.util.Iterator<T> {
    AVLNode<T> node;
    Stack<AVLNode<T>> stack;

    public AVLIteratorPostOrder(AVLNode<T> node, int BSTSize){
        this.node = node;
        stack = new ArrayStack<>(BSTSize);
        populateStack(stack, this.node);
    }

    private void populateStack(Stack<AVLNode<T>> st, AVLNode<T> n){
        if(n == null)
            return;
        populateStack(st,n.direito);
        st.push(n);
        populateStack(st,n.esquerdo);
    }

    public boolean hasNext(){
        return !stack.empty();
    }

    public T next() {
        return stack.pop().elemento;
    }

}
