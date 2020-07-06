package com.example.demo.Rest.Responses
        ;
import lombok.Data;
import org.springframework.beans.factory.annotation.Value;

@Data
public class RegistryDetails {

    @Value("#{target.id}")
    public long id;
    
    @Value("#{target.username}")
    public String username;
    
    @Value("#{target.level}")
    public int level;
    
    @Value("#{target.super_name}")
    public String super_name;    
    
}
