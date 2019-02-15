package EDA1;

public interface List<T> {
    java.util.Iterator<T> iterator();

    int size();

    boolean isEmpty();

    void removeIndex(int i);

    void remove(T x);

    void add(T x);

    void add(int i, T x);

    T get(int i);

    void set(int i, T y);

    String toString();
}
