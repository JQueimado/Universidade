/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package paral04;

import com.sun.corba.se.spi.orbutil.threadpool.ThreadPool;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

/**
 *
 * @author joao
 */
public class Paral04 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
    
        ExecutorService pool = Executors.newFixedThreadPool(4);
        
        int i;
        
        int start = 0;
        int increment = 50000;
        
        for (i = start; i<4*increment; i+= increment){
            pool.submit(new Primos(i, i+increment));
        }
        
        pool.shutdown();
        
        try{
            pool.awaitTermination(1000, TimeUnit.MILLISECONDS);
        } catch( InterruptedException e){
            
        }
    }
    
}
