package com.example.demo.Rest.Responses;

import java.io.Serializable;

public class TextResponse implements Serializable{

    private final String text;
     
    public TextResponse( String text ) {
        
        this.text = text;
        
    }

    public String getText() {
        return text;
    }

}
