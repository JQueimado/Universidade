package EDA1;

public class AVLNode<T> {
    T elemento;
    AVLNode<T> esquerdo;
    AVLNode<T> direito;
    int altura;

    public AVLNode(T e) {
        elemento = e;
        esquerdo = null;
        direito = null;
        altura = 1;
    }

    public AVLNode(T e, AVLNode<T> esquerdo, AVLNode<T> direito) {
        elemento = e;
        this.esquerdo = esquerdo;
        this.direito = direito;
        altura = 1;
    }

    public String toString() {
        return elemento.toString();
    }
}
