/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package paral04;

import java.util.concurrent.RecursiveAction;

/**
 *
 * @author joao
 */
public class PrimosRecurciveAction extends RecursiveAction
{
    
    private int start, end, result;
    
    public PrimosRecurciveAction( int start, int end )
    {
        super();
        this.start = start;
        this.end = end;
        this.result = 0;
    }
    
    private int calculo()
    {
        int c = 0;
        boolean cool;
        int i, j;
        
        for (i = this.start; i< this.end; i++)
        {
            cool = true;
            for (j = 2; j<i && i>=2 ; j++)
            {
                if( i%j == 0 )
                {
                    break;
                }  
            }
            if ( i == j )
                c++;
        }
        
        return c;
    } 
    
    public int getResult(){
        return this.result;
    }
    
    @Override
    public void compute()
    {
        if ( this.start - this.end <= 50000 )
        {
            this.result = calculo();
        }
        else
        {
            int mid = (this.end - this.start)/2 + this.start;
            PrimosRecurciveAction p1 = new PrimosRecurciveAction(this.start, mid);
            PrimosRecurciveAction p2 = new PrimosRecurciveAction(mid, this.end );
            
            invokeAll(p1,p2);
            
            this.result = p1.getResult() + p2.getResult();
        }
    }
    
}
