package com.example.demo.Rest.Responses;

import java.io.Serializable;

public class TextResponse implements Serializable{
 
    public static final String OK_STATUS = "OK";
    public static final String ER_STATUS = "ERROR";
    
    private final String text;
    private final String status;
     
    public TextResponse( String text, String status) {
        
        this.text = text;
        this.status = status;
        
    }

    public String getText() {
        return text;
    }

    public String getStatus() {
        return status;
    }
    
}
