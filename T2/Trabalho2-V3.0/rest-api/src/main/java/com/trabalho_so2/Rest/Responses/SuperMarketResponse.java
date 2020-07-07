package com.trabalho_so2.Rest.Responses;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import lombok.Data;

@Data
public class SuperMarketResponse {
    
    private String super_name;

    private int level1;
    private int level2;
    private int level3;
    private int level4;
    
    public void add(int i){
        switch(i){
            case 1:
                level1+=1;
                break;
            case 2:
                level2+=1;
                break;
            case 3:
                level3+=1;
                break;
            case 4:
                level4+=1;
                break;
        }
    }
    
}
