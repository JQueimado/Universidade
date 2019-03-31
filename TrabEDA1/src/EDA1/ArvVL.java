package EDA1;

import java.util.Iterator;

public class ArvVL<T extends Comparable<? super T>> implements Iterable<T>, AVL<T> {

    private AVLNode<T> node;
    private int tamanho;

    public ArvVL(T x) {
        node = new AVLNode<>(x);
        tamanho = 1;
    }

    public ArvVL(AVLNode<T> x) {
        node = x;
        tamanho = 0;
    }

    public ArvVL() {
        node = null;
        tamanho = 0;
    }

    public ArvVL(T x, AVLNode<T> left, AVLNode<T> right) {
        node = new AVLNode<>(x, left, right);
        tamanho = 3;
    }

    @Override
    public boolean isEmpty() {
        return node == null;
    }

    @Override
    public boolean contains(T x) {
        return contains(x, node);
    }

    private boolean contains(T x, AVLNode<T> n) {
        if (n == null)
            return false;
        if (n.elemento.compareTo(x) == 0)
            return true;

        if (x.compareTo(n.elemento) < 0)
            return contains(x, n.esquerdo);
        else
            return contains(x, n.direito);

    }

    @Override
    public T findMin() {
        return findMin(node).elemento;
    }

    private AVLNode<T> findMin(AVLNode<T> n) {
        AVLNode<T> current = n;
        while (current.esquerdo != null) {
            current = current.esquerdo;
        }
        return current;
    }

    @Override
    public T findMax() {
        return findMax(node).elemento;
    }

    private AVLNode<T> findMax(AVLNode<T> n) {
        AVLNode<T> current = n;
        while (current.direito != null) {
            current = current.direito;
        }
        return current;
    }


    @Override
    public void insert(T x) {
        node = insert(x, node);
        tamanho++;
    }

    private AVLNode<T> insert(T x, AVLNode<T> n) {
        if (n == null)
            return new AVLNode<>(x);

        if (x.compareTo(n.elemento) < 0)
            n.esquerdo = insert(x, n.esquerdo);
        else if (x.compareTo(n.elemento) > 0)
            n.direito = insert(x, n.direito);
        else
            return n;

        n.altura = 1 + Math.max(height(n.esquerdo), height(n.direito));

        int balance = getBalance(n);


        if (balance > 1 && x.compareTo(n.esquerdo.elemento) < 0)
            return simpleRightRotation(n);


        if (balance < -1 && x.compareTo(n.direito.elemento) > 0)
            return simpleLeftRotation(n);


        if (balance > 1 && x.compareTo(n.esquerdo.elemento) > 0)
            return leftRightRotation(n);


        if (balance < -1 && x.compareTo(n.direito.elemento) < 0)
            return rightLeftRotation(n);

        return n;
    }


    @Override
    public void remove(T x) {
        if (!isEmpty()) {
            if (contains(x)) {
                tamanho--;
                node = remove(x, node);
            }
        }
    }

    private AVLNode<T> remove(T x, AVLNode<T> n) {

        if (n == null)
            return n;

        if (x.compareTo(n.elemento) < 0) {
            n.esquerdo = remove(x, n.esquerdo);
        } else if (x.compareTo(n.elemento) > 0) {
            n.direito = remove(x, n.direito);
        } else {
            if (n.esquerdo == null || n.direito == null) {
                AVLNode<T> temp = null;
                if (temp == n.esquerdo)
                    temp = n.direito;
                else
                    temp = n.esquerdo;


                if (temp == null) {
                    temp = n;
                    n = null;
                } else
                    n = temp;
            } else {
                AVLNode<T> temp = findMin(n.direito);

                n.elemento = temp.elemento;

                n.direito = remove(temp.elemento, n.direito);
            }
        }

        if (n == null)
            return n;

        n.altura = Math.max(height(n.esquerdo), height(n.direito)) + 1;

        int balance = getBalance(n);

        if (balance > 1 && getBalance(n.esquerdo) >= 0)
            return simpleRightRotation(n);


        if (balance > 1 && getBalance(n.esquerdo) < 0) {
            return leftRightRotation(n);
        }


        if (balance < -1 && getBalance(n.direito) <= 0)
            return simpleRightRotation(n);


        if (balance < -1 && getBalance(n.direito) > 0) {
            return rightLeftRotation(n);
        }

        return n;
    }

    @Override
    public void printInOrder() {
        printInOrder(node);
    }

    private void printInOrder(AVLNode<T> n) {
        if (n == null)
            return;

        printInOrder(n.esquerdo);

        System.out.print(n.elemento + "  ");

        printInOrder(n.direito);
    }

    @Override
    public void printPostOrder() {
        printPostOrder(node);
    }

    private void printPostOrder(AVLNode<T> n) {
        if (n == null)
            return;

        printPostOrder(n.esquerdo);

        printPostOrder(n.direito);

        System.out.print(n.elemento + " ");
    }

    @Override
    public void printPreOrder() {
        printPreOrder(node);
    }

    private void printPreOrder(AVLNode<T> n) {
        if (n == null)
            return;

        System.out.print(n.elemento + " ");

        printPreOrder(n.esquerdo);

        printPreOrder(n.direito);
    }

    @Override
    public Iterator<T> iterator() {
        return new AVLIteratorPostOrder<>(node, tamanho);
    }


    private AVLNode<T> simpleRightRotation(AVLNode<T> n0) {

        AVLNode<T> n1 = n0.esquerdo;
        n0.esquerdo = n1.direito;
        n1.direito = n0;

        n0.altura = Math.max(height(n0.esquerdo), height(n0.direito)) + 1;
        n1.altura = Math.max(height(n1.direito), height(n1.esquerdo)) + 1;

        return n1;
    }

    private AVLNode<T> simpleLeftRotation(AVLNode<T> n0) {

        AVLNode<T> n1 = n0.direito;
        n0.direito = n1.esquerdo;
        n1.esquerdo = n0;

        n0.altura = Math.max(height(n0.esquerdo), height(n0.direito)) + 1;
        n1.altura = Math.max(height(n1.direito), height(n1.esquerdo)) + 1;

        return n1;
    }

    private AVLNode<T> rightLeftRotation(AVLNode<T> n0) {

        AVLNode<T> n1 = n0.direito;
        n0.direito = simpleRightRotation(n1);

        n0.altura = Math.max(height(n0.esquerdo), height(n0.direito)) + 1;
        n1.altura = Math.max(height(n1.direito), height(n1.esquerdo)) + 1;

        return simpleLeftRotation(n0);
    }

    private AVLNode<T> leftRightRotation(AVLNode<T> n0) {

        AVLNode<T> n1 = n0.esquerdo;
        n0.esquerdo = simpleLeftRotation(n1);

        n0.altura = Math.max(height(n0.esquerdo), height(n0.direito)) + 1;
        n1.altura = Math.max(height(n1.direito), height(n1.esquerdo)) + 1;

        return simpleRightRotation(n0);
    }

    private int height(AVLNode<T> n) {
        if (n == null)
            return 0;

        return n.altura;
    }

    private int getBalance(AVLNode<T> n) {
        if (n == null)
            return 0;

        return height(n.esquerdo) - height(n.direito);
    }
}

