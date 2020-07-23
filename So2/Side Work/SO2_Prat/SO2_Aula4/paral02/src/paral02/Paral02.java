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
public class Paral02 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        int counter = 0;
        int increment = 50000;
        
        
        PrimoThread p1 = new PrimoThread(counter, counter + increment);
        
        counter += increment;
        PrimoThread p2 = new PrimoThread(counter, counter + increment);
        
        counter += increment;
        PrimoThread p3 = new PrimoThread(counter, counter + increment);
        
        counter += increment;
        PrimoThread p4 = new PrimoThread(counter, counter + increment);
        
        p1.start();
        p2.start();
        p3.start();
        p4.start();
    }
    
}
