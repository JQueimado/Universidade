/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package testapp;

/**
 *
 * @author joao
 */
public class Test2 
{
    
    public static void main(String[] args) 
    {
        
        try
        {
            byte[] byts = new byte[128];
            int size = System.in.read(byts);
            int val = Integer.parseInt((new String(byts)).substring(0, size-1) );
            System.out.println( val + 1 );
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }
    
}
