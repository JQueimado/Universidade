package com.trabalho_so2.Rest.Request;

/*
JSON
{
    name: String
}
*/

public class SuperMarketRequest {
    
    private String name;
    
    public SuperMarketRequest(String name){
        this.name = name;
    }
    
    public SuperMarketRequest(){
        this.name = "no name";
    }
 
    public String getName(){
        return this.name;
    }
    
    public void setName(String name ){
        this.name = name;
    }
    
}
