import EDA1.DoubleLinkedList;
import EDA1.LinkedList;
import EDA1.ArrayQueue;
import java.util.Iterator;

public class AgendaTele {
    private DoubleLinkedList<LinkedList<String>> lista = new DoubleLinkedList();

    public AgendaTele() {
        this.lista = new DoubleLinkedList();
    }

    public void addContacto(String nome, String numero) {
        LinkedList<String> node = new LinkedList();
        node.add(nome);
        node.add(numero);
        this.lista.add(node);
    }

    public void sort() {
        for(int i = 1; i < lista.size(); ++i) {
            for(int j = 0; j < this.lista.size() - 1; ++j) {
                String a = lista.getElement(i).get(0);
                String b = lista.getElement(j).get(0);
                if (a.compareToIgnoreCase(b)<0) {
                    LinkedList<String> nodeJ = lista.getElement(j);
                    LinkedList<String> nodeI = lista.getElement(i);
                    lista.set(j,nodeI);
                    lista.set(i,nodeJ);
                }
            }
        }

    }

    public void listarContatos() {
        if(lista.size()==0){
            System.out.println("Nenhum Contacto na lista");
            return;
        }

        this.sort();
        Iterator var1 = this.lista.iterator();

        System.out.println("Lista:");

        while(var1.hasNext()) {
            LinkedList<String> node = (LinkedList)var1.next();
            System.out.println(" " + (String)node.get(0) + "-" + (String)node.get(1) + ";");
        }

    }

    public void modificarContactoNome(String valor, String nValor) throws Exception {
        int indice = this.procurarNome(valor);
        if (indice == -1) {
            throw new Exception("Error 404-Contacto not found!");
        } else {
            LinkedList<String> current = (LinkedList)this.lista.getElement(indice);
            current.set(0, nValor);
        }
    }

    public void modificarContactoNum(String valor, String nValor) throws Exception {
        int indice = this.procurarNome(valor);
        if (indice == -1) {
            throw new Exception("Error 404-Contacto not found!");
        } else {
            LinkedList<String> current = (LinkedList)this.lista.getElement(indice);
            current.set(1, nValor);
        }
    }

    public int procurarNome(String nome) {
        for(int i = 0; i < this.lista.size(); ++i) {
            LinkedList<String> current = lista.getElement(i);
            if (current.get(0).compareTo(nome)==0) {
                return i;
            }
        }
        return -1;
    }

    public String getTele(int i){
        return lista.getElement(i).get(1);
    }

    public void removerContacto(String Nome) {
        int indice = this.procurarNome(Nome);
        this.lista.remove(indice);
    }

    public ArrayQueue<String> returnarQ() {
        ArrayQueue<String> Temp = new ArrayQueue(lista.size()*2);

        for(int i = 0; i < this.lista.size(); ++i) {
            Temp.enqueue((String)((LinkedList)this.lista.getElement(i)).get(0));
            Temp.enqueue((String)((LinkedList)this.lista.getElement(i)).get(1));
        }

        return Temp;
    }
}