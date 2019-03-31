package EDA1;

public interface AVL<T extends Comparable<? super T>>{
    boolean isEmpty();
    boolean contains(T x);
    T findMin();
    T findMax();
    void insert(T x);
    void remove(T x);
    void printInOrder();
    void printPostOrder();
    void printPreOrder();
}
