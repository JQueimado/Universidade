package com.trabalho_so2.Rest.Responses;

import lombok.Data;

/*
JSON
{
    super_name:String
    empty_or_with_minimum_ocupation:int
    with_people_but_with_enouth_space:int
    overcrowded:int
    overcrowded_with_a_big_queue:int
}

*/

@Data
public class SuperMarketResponse {
    
    private String super_name;

    private int empty_or_with_minimum_ocupation;
    private int with_people_but_with_enouth_space;
    private int overcrowded;
    private int overcrowded_with_a_big_queue;
    
    public void add(int i){
        switch(i){
            case 1:
                empty_or_with_minimum_ocupation+=1;
                break;
            case 2:
                with_people_but_with_enouth_space+=1;
                break;
            case 3:
                overcrowded+=1;
                break;
            case 4:
                overcrowded_with_a_big_queue+=1;
                break;
        }
    }
    
}
