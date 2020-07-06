package com.example.demo;

import com.trabalho_so2.Jwt.JwtTool;
import com.trabalho_so2.Rest.Request.JwtRequest;
import com.trabalho_so2.Rest.Responses.JwtResponse;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.assertj.core.api.Assertions.assertThat;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.boot.test.web.client.TestRestTemplate;
import org.springframework.boot.web.server.LocalServerPort;

@SpringBootTest(webEnvironment = SpringBootTest.WebEnvironment.RANDOM_PORT)
public class HttpTestasdwda {
    
    @LocalServerPort
    private int port;
    
    @Autowired
    private TestRestTemplate restTemplate;
    
    @Autowired
    private JwtTool tools;
    
    private final String url = "https://localhost:"+port+"/";
    
    @Test
    public void login_should_succeed() throws Exception{
        // Standart user 
        JwtRequest request = new JwtRequest("admin", "admin");
        
        JwtResponse response = this.restTemplate.postForObject( this.url+"login", request, JwtResponse.class ) ;
        
        System.out.println(response.getToken());
        
        assertFalse(response.getToken().isEmpty());
        assertFalse(response.getToken().isBlank());
        assertThat(tools.getUsernameFromToken(response.getToken())).contains("admin");
    }
    
}
