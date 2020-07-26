/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package so2;

import java.sql.ResultSet;
import java.sql.Statement;
import java.util.Arrays;
import java.util.Vector;

/**
 *
 * @author joao
 */
public class Avaliação {

    /**
     * @param args the command line arguments
     */
    
    /*
        Gets a list of alunos
    */
    public static Vector<Integer> getAlunos(Statement stmt) throws Exception{
        
        String quarry = "Select n from aluno;";
        
        //Get quarry 
        ResultSet rs = stmt.executeQuery(quarry);
        
        // Convert to Vector
        Vector<Integer> list = new Vector();
        
        while ( rs.next() )
            list.add( rs.getInt("n") );
        
        return list;
    }
    
    /*
        Gets a list of disciplinas
    */
    public static Vector<Integer> getDisciplinas(Statement stmt) throws Exception{
        
        String quarry = "Select codigo from disciplina;";
        
        //Get quarry 
        ResultSet rs = stmt.executeQuery(quarry);
        
        // Convert to Vector
        Vector<Integer> list = new Vector();
        
        while ( rs.next() )
            list.add( rs.getInt("codigo") );
        
        return list;
    }
    
    /*
        +++ MAIN +++
    */
    public static void main(String[] args) {
        // TODO code application logic here
        try
        {
            if (args.length < 1)
                throw new Exception("Invalid argument size");
            
            // Connection setup
            PostgresConnector pc = new PostgresConnector("localhost", "bd1", "user1", "1234");
            pc.connect();
            Statement stmt = pc.getStatement();
            System.out.println("Connected to postgress...\n runnig op...");
            
            /*
            for (String a: args){
                System.out.println(a);
            }
            */
            
            // Command Interp
            switch ( args[0] )
            {
                
                // Register aluno
                case "a":
                {
                    System.out.println("Register Aluno");
                    
                    if ( args.length != 5 )
                        throw new Exception("invalid size for op a");
                    
                    String quary = "insert into aluno values("+args[1]+", '"+args[2]+"', "+args[3]+", "+args[4]+");";
                    
                    //System.out.println(quary);
                    
                    stmt.executeUpdate(quary);
                }
                break;
                
                // Register Disciplina
                case "d":
                {
                    System.out.println("Register Disciplina");
                    
                    if ( args.length != 4 )
                        throw new Exception("invalid size for op d");
                    
                    String quary = "insert into disciplina values("+args[1]+", '"+args[2]+"', '"+args[3]+"');";
                    
                    //System.out.println(quary);
                    
                    stmt.executeUpdate(quary);
                    
                }
                break;
                
                // Inscrever
                case "i":
                {
                    System.out.println("Inscrever");
                    
                    if( args.length != 3)
                        throw new Exception("invalid size for op i");
                    
                    // process Aluno
                    int n = Integer.parseInt(args[1]);
                    Vector<Integer> aux = getAlunos(stmt);
                    
                    if (!aux.contains(n))
                        throw new Exception("Aluno does not exist");
                    
                    // process disciplina
                    n = Integer.parseInt(args[2]);
                    aux = getDisciplinas(stmt);
                    
                    if (!aux.contains(n))
                        throw new Exception("Disciplina does not exist");
                    
                    String quarry = "insert into inscricao values( "+ args[1] +", "+ args[2] +" );";
                    
                    stmt.executeUpdate(quarry);
                    
                }
                break;
                
                // list Aluno
                case "la":
                {
                    System.out.println("List Alunos");
                    if ( args.length != 1 )
                        throw new Exception("invalid size for op la");
                    
                    String query = "select * from aluno;";
                    
                    //System.out.println(quary);
                    
                    ResultSet rs = stmt.executeQuery(query);
                    
                    System.out.format("|%10s|%10s|%10s|%s\n", 
                            "n",
                            "nome",
                            "bi",
                            "telefone");
                    
                    while ( rs.next() )
                    {
                        System.out.format("|%10d|%10s|%10d|%d\n", 
                                rs.getInt("n"), 
                                rs.getString("nome"), 
                                rs.getInt("bi"),
                                rs.getInt("telefone"));
                    }
                    
                }
                break;
                
                // List Disciplinas
                case "ld":
                {
                    System.out.println("List Disciplinas");
                    
                    if ( args.length != 1 )
                        throw new Exception("invalid size for op ld");
                    
                    String query = "select * from disciplina;";
                    
                    //System.out.println(quary);
                    
                    ResultSet rs = stmt.executeQuery(query);
                    
                    System.out.format("|%10s|%10s|%s\n", 
                            "codigo",
                            "nome",
                            "descricao");
                    
                    while ( rs.next() )
                    {
                        System.out.format("|%10d|%10s|%s\n", 
                                rs.getInt("codigo"), 
                                rs.getString("nome"), 
                                rs.getString("descricao"));
                    }
                    
                }
                break;
                
                // List Inscrições
                case "li":
                {
                    System.out.println("List Inscricoes");
                    
                    if ( args.length != 1 )
                        throw new Exception("invalid size for op li");
                    
                    String query = "select * from inscricao;";
                    
                    //System.out.println(quary);
                    
                    ResultSet rs = stmt.executeQuery(query);
                    
                    System.out.format("|%10s|%10s\n", 
                            "n",
                            "codigo");
                    
                    while ( rs.next() )
                    {
                        System.out.format("|%10d|%10d\n", 
                                rs.getInt("n"), 
                                rs.getInt("codigo"));
                    }
                    
                }
                break;
                
                // list Aluno Inscrito
                case "lai":
                {
                    System.out.println("List Alunos Inscritos");
                    if ( args.length != 2 )
                        throw new Exception("invalid size for op lai");
                    
                    String query = "select n, nome, bi, telefone from aluno natural join inscricao where codigo= "+ args[1] +" ;";
                    
                    //System.out.println(quary);
                    
                    ResultSet rs = stmt.executeQuery(query);
                    
                    System.out.format("|%10s|%10s|%10s|%s\n", 
                            "n",
                            "nome",
                            "bi",
                            "telefone");
                    
                    while ( rs.next() )
                    {
                        System.out.format("|%10d|%10s|%10d|%d\n", 
                                rs.getInt("n"), 
                                rs.getString("nome"), 
                                rs.getInt("bi"),
                                rs.getInt("telefone"));
                    }
                    
                }
                break;
                
                // List Disciplina Inscrito
                case "ldi":
                {
                    System.out.println("List Disciplina Inscritos");
                    if ( args.length != 2 )
                        throw new Exception("invalid size for op lai");
                    
                    String query = "select codigo, nome, descricao from disciplina natural join inscricao where n="+ args[1] +" ;";
                    
                    //System.out.println(quary);
                    
                    ResultSet rs = stmt.executeQuery(query);
                    
                    System.out.format("|%10s|%10s|%s\n", 
                            "codigo",
                            "nome",
                            "descricao");
                    
                    while ( rs.next() )
                    {
                        System.out.format("|%10d|%10s|%s\n", 
                                rs.getInt("codigo"), 
                                rs.getString("nome"), 
                                rs.getString("descricao"));
                    }
                    
                }
                break;
                
                default:
                {
                    throw new Exception("invalid op");
                }
                    
            }
            
            System.out.println("op Sucessfull");
        }
        catch (Exception e)
        {
            System.out.println(e.getMessage());
            e.printStackTrace();
        }
        
    }
    
}
