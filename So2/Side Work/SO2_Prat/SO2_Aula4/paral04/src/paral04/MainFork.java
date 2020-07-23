/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package paral04;

import java.util.concurrent.ForkJoinPool;

/**
 *
 * @author joao
 */
public class MainFork {
    
    public static void main(String[] args) {
        
        PrimosRecurciveAction p = new PrimosRecurciveAction(0, 200000);
        
        ForkJoinPool pool = new ForkJoinPool();
        
        System.out.println( pool.getParallelism() ); 
        
        pool.invoke(p);
            
        System.out.println("found: "+ p.getResult());
    }
    
}
