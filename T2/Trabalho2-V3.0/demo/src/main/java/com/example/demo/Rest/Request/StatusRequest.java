package com.example.demo.Rest.Request;

public class StatusRequest {
    
    private String method;

    public StatusRequest(String method) {
        this.method = method;
    }
    
    public StatusRequest(){
        
    }

    public String getMethod() {
        return method;
    }

    public void setMethod(String method) {
        this.method = method;
    }
    
}
