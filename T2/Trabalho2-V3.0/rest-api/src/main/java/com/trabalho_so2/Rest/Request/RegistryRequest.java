package com.trabalho_so2.Rest.Request;

/*
JSON
{
    superName: String,
    ocup:int
}
*/

public class RegistryRequest {
    
    private String superName;
    private int ocup;

    public RegistryRequest(String superName, int ocup) {
        this.superName = superName;
        this.ocup = ocup;
    }

    public RegistryRequest() {
    }

    public String getSuperName() {
        return superName;
    }

    public void setSuperName(String superName) {
        this.superName = superName;
    }

    public int getOcup() {
        return ocup;
    }

    public void setOcup(int ocup) {
        this.ocup = ocup;
    }
    
    
    
}
