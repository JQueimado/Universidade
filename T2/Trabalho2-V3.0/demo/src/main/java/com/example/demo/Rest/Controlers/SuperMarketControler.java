package com.example.demo.Rest.Controlers;

import com.example.demo.DB.Entities.SuperMarket;
import com.example.demo.DB.Repositories.SuperMarketRepository;
import com.example.demo.Rest.Request.SuperMarketRequest;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpMethod;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import static org.springframework.http.ResponseEntity.ok;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/supermarkets")
public class SuperMarketControler {
    
    @Autowired
    private SuperMarketRepository supermarkets;
    
    //Get All Super Markets
    @GetMapping("")
    public ResponseEntity all() {
        return ResponseEntity.ok().header("Access-Control-Allow-Origin","*").body(supermarkets.findAll());
    }    
    
    //Options Handler
    @RequestMapping( value = "", method = RequestMethod.OPTIONS)
    public ResponseEntity getOption(){
        return ResponseEntity.ok().allow(HttpMethod.POST, HttpMethod.OPTIONS, HttpMethod.GET).header("Access-Control-Allow-Headers","Authorization").build();
    }
    
    //Create Handler
    @RequestMapping( value = "", method = RequestMethod.POST)
    public ResponseEntity addSuperMarket( @RequestBody SuperMarketRequest request ){
        try{
            SuperMarket nsp = new SuperMarket();
            nsp.setName(request.getName());

            System.out.println("Adding "+ request.getName() +" to the data base");
            
            supermarkets.save(nsp);

            return ResponseEntity.ok(request);
        }catch( Exception e){
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).build();
        }
        
    }
    
}
