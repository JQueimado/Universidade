package com.example.demo.Rest.Controlers;

import com.example.demo.DB.Entities.Registry;
import com.example.demo.DB.Entities.SuperMarket;
import com.example.demo.DB.Repositories.RegistryRepository;
import com.example.demo.DB.Repositories.SuperMarketRepository;
import com.example.demo.Jwt.JwtTool;
import com.example.demo.Rest.Request.RegistryRequest;
import com.example.demo.UserDB.Entities.User;
import com.example.demo.UserDB.Repositories.UserRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import static org.springframework.http.ResponseEntity.ok;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestHeader;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/registries")
public class RegistryController {
    
    @Autowired
    private RegistryRepository registries;
    
    @Autowired
    private UserRepository users;
    
    @Autowired
    private SuperMarketRepository supermarkets;
    
    @Autowired
    private JwtTool jwtTokenUtil;
    
    // GET All
    @RequestMapping(value =  "/all", method = RequestMethod.GET)
    public ResponseEntity all() {
        return ResponseEntity
                .ok()
                .header("Access-Control-Allow-Origin","*")
                .body(registries.findAll());
    }    
    
    // GET One
    @RequestMapping(value =  "/{id}", method = RequestMethod.GET)
    public ResponseEntity findOne( @PathVariable("id") long id){
        
        return ResponseEntity
                .ok()
                .header("Access-Control-Allow-Origin","*")
                .body(registries.findById(id));
        
    }
    
    // POST new registry
    @RequestMapping(value = "/new", method = RequestMethod.POST)
    public ResponseEntity newReg( 
            @RequestHeader("Authorization") String token, 
            @RequestBody RegistryRequest registry ){
        
         if( !token.startsWith("Bearer") )
            return ResponseEntity.status(HttpStatus.UNAUTHORIZED).build();
        
        token = token.substring(7);
        
        // Find User that sent the mesage
        String username = jwtTokenUtil.getUsernameFromToken(token);
        
        System.out.println("User:" +username);
        System.out.println("Super:"+ registry.getSuperName());
        
        User user = users.findByUsername(username);
        SuperMarket sm = supermarkets.findByName(registry.getSuperName());
        
        Registry nRes = new Registry();
        nRes.setLevel(registry.getOcup());
        
        user.getRegistry().add(nRes);
        sm.getRegistries().add(nRes);
        
        registries.save(nRes);
        
        return ResponseEntity
                .status(HttpStatus.CREATED)
                .header("Access-Control-Allow-Origin","*")
                .build();
        
    }
    
    // GET All form User
    @RequestMapping(value =  "/user", method = RequestMethod.GET)
    public ResponseEntity findByUser( @RequestHeader("Authorization") String token ){
        
        if( !token.startsWith("Bearer") )
            return ResponseEntity.status(HttpStatus.UNAUTHORIZED).build();
        
        token = token.substring(7);
        
        // Find User that sent the mesage
        String username = jwtTokenUtil.getUsernameFromToken(token);
        
        return ResponseEntity
                .ok()
                .header("Access-Control-Allow-Origin","*")
                .body(users.findByUsername(username).getRegistry());
        
    }
    
}
