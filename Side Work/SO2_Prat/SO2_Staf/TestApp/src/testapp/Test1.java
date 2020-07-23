/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package testapp;

/* imports */
import java.util.Vector;

/**
 *
 * @author joao
 */
public class Test1 
{
    /* Insertion Sort */
    private static void insert( String s, Vector<String> v  )
    {
        int pos;
        String ss;
        
        // lookup
        for( pos = 0; pos < v.size()-1; pos++ )
        {
            ss = v.get(pos); 
            
            if( ss.compareTo(s) == 1 )
            {
                v.insertElementAt(s, pos);
                return;
            }
        }
        
        //not found
        v.add( s );
        return;

    }
    
    private static Vector<String> insertionSort( Vector<String> v )
    {
        Vector<String> ret = new Vector();
        
        for( String s: v )
            insert( s, ret);
        
        return ret;
    }
    
    /* Main */
    public static void main(String[] args)
    {
        Vector<String> v = new Vector();
        
        for (String arg: args)
        {
            v.add(arg);
        }
        
        Vector n = insertionSort( v );
        
        System.out.println(n.toString());
        
        System.out.println("Done");
    }
}
