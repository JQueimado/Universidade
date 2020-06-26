package com.example.demo.RestControlers;

import com.example.demo.Repositories.SuperMarketRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import static org.springframework.http.ResponseEntity.ok;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/supermarkets")
public class SuperMarketControler {
    
    @Autowired
    private SuperMarketRepository supermarkets;
    
    @GetMapping("")
    public ResponseEntity all() {
        return ok(this.supermarkets.findAll());
    }    
    
    
}
