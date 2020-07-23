/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package paral04;

/**
 *
 * @author joao
 */
public class Primos implements Runnable{
    
    private int start, end;
    
    public Primos( int start, int end ){
        super();
        this.start = start;
        this.end = end;
    }
    
    public void setStart(int val){
        this.start = val;
    }
    
    public void setEnd(int val){
        this.end = val;
    }
    
    private int calculo(){
        int c = 0;
        boolean cool;
        int i, j;
        
        for (i = this.start; i< this.end; i++){
            cool = true;
            for (j = 2; j<i && i>=2 ; j++){
                if( i%j == 0 ){
                    break;
                }  
            }
            if ( i == j )
                c++;
        }
        
        return c;
    } 
    
    public void go(){
        
        int res = calculo();
        
        System.out.println("found: "+ res);
        
    }
    
    public void run (){
        int res = calculo();
        
        System.out.println("found: "+ res);
    }
}
