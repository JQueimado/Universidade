/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package paral02;

/**
 *
 * @author joao
 */
public class PrimoThread extends Thread { 
    
    int start, end;
    
    public PrimoThread( int start, int end ){
        super();
        
        this.start = start;
        this.end = end;
        
    }
    
    public void run(){
        Primos p = new Primos(this.start, this.end);
        
        p.go();
    }
    
}
