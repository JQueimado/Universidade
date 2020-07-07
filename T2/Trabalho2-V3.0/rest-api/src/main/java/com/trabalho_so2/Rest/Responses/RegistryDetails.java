package com.trabalho_so2.Rest.Responses
        ;
import lombok.Data;

/*
JSON
{
    id:long/int,
    username: String,
    level:long/int,
    super_name:String
}
*/

@Data
public class RegistryDetails {

    public long id;
    
    public String username;
    
    public int level;
    
    public String super_name;    
    
}
