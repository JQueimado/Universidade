/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cifra;

import java.security.*;

/**
 *
 * @author joao
 */
public class Cifra {

    /**
     * @param args the command line arguments
     */
    public static void main( String[] args ) {

        Provider[] providers = java.security.Security.getProviders();
        
        for (Provider p: providers)
        {
            System.out.println( "p: "+ p.getName() +" v: "+ p.getVersion() );
        }
        
    }
    
}
