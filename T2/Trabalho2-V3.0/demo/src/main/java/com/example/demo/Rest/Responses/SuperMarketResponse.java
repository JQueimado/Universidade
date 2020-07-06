package com.example.demo.Rest.Responses;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

public class SuperMarketResponse {
    
    private String super_name;
    
    private List<Integer> levels;

    public SuperMarketResponse(){
        this("", new ArrayList());
    }
    
    public SuperMarketResponse(String super_name, List<Integer> levels) {
        this.super_name = super_name;
        this.levels = levels;
    }
    
    public String getSuper_name() {
        return super_name;
    }

    public void setSuper_name(String super_name) {
        this.super_name = super_name;
    }

    public Collection<Integer> getLevels() {
        return levels;
    }

    public void setLevels(List<Integer> levels) {
        this.levels = levels;
    }
    
    
    
}
