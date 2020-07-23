package so2.db;

import java.sql.ResultSet;
import java.sql.Statement;

/**
 *
 * @author jsaias
 */
public class TesteAcessoBD {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws Exception {

        // coloque os argumentos
        
        PostgresConnector pc = new PostgresConnector( "localhost","bd1","user1","1234" );
        // NOTA: se isto nao fosse uma domonstacao, nao PODIA ter configuracoes no codigo fonte!!!
        
        
        // estabelecer a ligacao ao SGBD
        pc.connect();
        Statement stmt = pc.getStatement();

	// *******************
        // update/insert
        try {

           // AQUI: operacao para inserir um registo com o seu nome...
           stmt.executeUpdate("insert into pessoas values('DaMan','"+new java.util.Date()+"')");

        } catch (Exception e) {
            e.printStackTrace();
            System.err.println("Problems on insert...");
        }

	// ******************
        // query	
        try {
            
            // AQUI: codigo para realizar a CONSULTA
            ResultSet rs = stmt.executeQuery("SELECT * FROM pessoas;");
            
            while (rs.next()) {
                String name = rs.getString("name");
                String date = rs.getString("date");
 
                System.out.println("name: "+name+"date: "+ date);
            }
            rs.close(); // muito importante depois da consulta!
            
        } catch (Exception e) {
            e.printStackTrace();
            System.err.println("Problems retrieving data from db...");
        }

        // desligar do SGBD:
        pc.disconnect();
    }


}
