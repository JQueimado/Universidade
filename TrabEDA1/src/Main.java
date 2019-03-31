import java.util.InputMismatchException;
import java.util.Scanner;

public class Main {

    public static void main(String[] a) {
            boolean c = true;
            AgendaTele lista = new AgendaTele();

            while (c) {
                try {
                    System.out.println("");
                    System.out.println("Menu: ");
                    System.out.println("1-Adicionar Contacto");
                    System.out.println("2-Listar Contactos");
                    System.out.println("3-Editar Contactos");
                    System.out.println("4-Procurar Contactos");
                    System.out.println("5-Exportar ");
                    System.out.println("6-Remover");
                    System.out.println("0-Sair");

                    Scanner scanner = new Scanner(System.in);

                    int op = scanner.nextInt();

                    String Nome;
                    Integer nNum;

                    if (op == 1) {
                        System.out.println("Insira o nome do contacto:");
                        Nome = scanner.next();
                        System.out.println("Insira o numero do contacto:");
                        nNum = scanner.nextInt();
                        lista.addContacto(Nome,nNum.toString());
                    }

                    if (op == 2) {
                        lista.listarContatos();
                    }

                    if (op == 3) {
                            System.out.println("Insira o contacto que prentede modificar:");
                            Nome = scanner.next();
                            System.out.println("Pretende modificar: 1-Nome 2-Numero");
                            op = scanner.nextInt();
                            if (op == 1) {
                                String nNome;
                                System.out.println("Incira o nome do Contacto");
                                nNome = scanner.next();
                                lista.modificarContactoNome(Nome, nNome.toString());
                            }

                            if (op == 2) {
                                System.out.println("Incira o numero do Contacto");
                                nNum = scanner.nextInt();
                                lista.modificarContactoNum(Nome, nNum.toString());
                            }

                            if (op!=1 && op!=2) throw new InputMismatchException();
                    }

                    if (op == 4) {
                        System.out.println("Introduza o Nome do Contacto q pretende:");
                        Nome = scanner.next();
                        int i=lista.procurarNome(Nome);
                        System.out.println("Numero: "+lista.getTele(i));
                    }

                    if (op == 5) {
                        System.out.println("Queue:"+lista.returnarQ().toString());
                    }

                    if (op == 6) {
                        System.out.println("Introduza o Contacto q pretende remover:");
                        Nome = scanner.next();
                        lista.removerContacto(Nome);
                    }

                    if (op == 0) {
                        c = false;
                    }

                    if(op<0 || op>6) throw new InputMismatchException();

                }catch (InputMismatchException e){
                    System.out.println("Invalid Input: tenta outra vez");
                }catch (Exception e){
                    System.out.println(e.getMessage());
                }
            }

    }
}

