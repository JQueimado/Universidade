package com.trabalho_so2.Rest.Controlers;

import com.trabalho_so2.Components.UserDetailsServiceImpl;
import com.trabalho_so2.DB.Entities.Registry;
import com.trabalho_so2.DB.Entities.SuperMarket;
import com.trabalho_so2.DB.Repositories.RegistryRepository;
import com.trabalho_so2.DB.Repositories.SuperMarketRepository;
import com.trabalho_so2.Jwt.JwtTool;
import com.trabalho_so2.Rest.Request.RegistryRequest;
import com.trabalho_so2.Rest.Responses.RegistryDetails;
import com.trabalho_so2.Rest.Responses.TextResponse;
import com.trabalho_so2.UserDB.Entities.User;
import com.trabalho_so2.UserDB.Repositories.UserRepository;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.Optional;
import javax.transaction.Transactional;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.CrossOrigin;
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
    private UserDetailsServiceImpl userDetailsService;
    
    @Autowired
    private SuperMarketRepository supermarkets;
    
    @Autowired
    private JwtTool jwtTokenUtil;
    
    /*Get all
    path : /registries/all
    method: GET
    expected body: indiferent
    responses:
        - status: OK                    body: Array( json.int.id, json.String.username, json.int.level, json.String.super_name )
        - status: INTERNAL_SERVER_ERROR body: json.text = "error getting ressorces"
    */
    @CrossOrigin
    @RequestMapping(value =  "/all", method = RequestMethod.GET)
    public ResponseEntity all() {
        
        try{
            
            Collection<Registry> _registies = registries.findAll();
            List<RegistryDetails> to_send = new ArrayList();
            
            for( Registry reg: _registies ){
                
                RegistryDetails temp = new RegistryDetails();
                temp.setId(reg.getId());
                temp.setLevel(reg.getLevel());
                temp.setSuper_name(supermarkets.findByRegId(reg.getId()).getName());
                temp.setUsername(users.findUserByRegistryId(reg.getId()).getUsername());
                to_send.add(temp);
            }
            
            return ResponseEntity
                .ok()
                .body(to_send);
            
        }catch(Exception e){
            e.printStackTrace();
            return ResponseEntity
                    .status(HttpStatus.INTERNAL_SERVER_ERROR)
                    .body(new TextResponse("error getting ressorces"));
        }
        
    }    
    
    /* New registry
    path : /registries/new
    method: POST
    expected body: json.String.superName, json.int.oucup
    responses:
        - status: CREATED               body: "created registry for {{json.String.superName}}"
        - status: INTERNAL_SERVER_ERROR body: json.text = "invalid Ocupation"
        - status: INTERNAL_SERVER_ERROR body: json.text = "supermarket {{json.String.superName}} not found"
        - status: INTERNAL_SERVER_ERROR body: json.text = "error"
    */
    @Transactional
    @CrossOrigin
    @RequestMapping(value = "/new", method = RequestMethod.POST)
    public ResponseEntity newReg( 
            @RequestHeader("Authorization") String token, 
            @RequestBody RegistryRequest registry ){
        
        try{
        
           if( registry.getOcup() > 4 || registry.getOcup() < 1 )
               return ResponseEntity
                    .status(HttpStatus.INTERNAL_SERVER_ERROR)
                    .body(new TextResponse("invalid Ocupation"));
            
           if( !token.startsWith("Bearer") )
              return ResponseEntity.status(HttpStatus.UNAUTHORIZED).build();

           token = token.substring(7);

           // Find User that sent the mesage
           String username = jwtTokenUtil.getUsernameFromToken(token);

           User user = users.findByUsername(username);
           SuperMarket sm = supermarkets.findByName(registry.getSuperName());

           if( sm == null)
               return ResponseEntity
                    .status(HttpStatus.INTERNAL_SERVER_ERROR)
                    .body(new TextResponse("supermarket "+registry.getSuperName()+" not found")); 
           
           Registry nRes = new Registry();
           nRes.setLevel(registry.getOcup());

           user.getRegistry().add(nRes);
           sm.getRegistries().add(nRes);

           registries.save(nRes);

        }catch(Exception e){
            e.printStackTrace();
            return ResponseEntity
                    .status(HttpStatus.INTERNAL_SERVER_ERROR)
                    .body(new TextResponse("error"));
        }
        
        return ResponseEntity
                .status(HttpStatus.CREATED)
                .body(new TextResponse("created registry for "+ registry.getSuperName()));
        
    }
    
    /* Get registries from user
    path : /registries/user
    method: GET
    expected body: indiferent
    responses:
        - status: OK           body: Array( json.int.id, json.String.username, json.int.level, json.String.super_name )
        - status: UNAUTHORIZED body: empty
    */
    @CrossOrigin
    @RequestMapping(value =  "/user", method = RequestMethod.GET)
    public ResponseEntity findByUser( @RequestHeader("Authorization") String token ){
        
        if( !token.startsWith("Bearer") )
            return ResponseEntity
                    .status(HttpStatus.UNAUTHORIZED)
                    .build();
        
        token = token.substring(7);
        
        // Find User that sent the mesage
        String username = jwtTokenUtil.getUsernameFromToken(token);
        
        List<RegistryDetails> to_send = new ArrayList<>();
        
        for(Registry reg : users.findByUsername(username).getRegistry()){
            RegistryDetails temp = new RegistryDetails();
            temp.setId(reg.getId());
            temp.setLevel(reg.getLevel());
            temp.setSuper_name( supermarkets.findByRegId(reg.getId()).getName() );
            temp.setUsername(username);
            to_send.add(temp);
        }
        
        return ResponseEntity
                .status(HttpStatus.OK)
                .body(to_send);
        
    }
    
    /* Remove Registry
    path : /registries/remove/{id}
    method: DELETE
    expected body: indiferent
    responses:
        - status: OK                    body: "removed registry with id {{id}}"
        - status: UNAUTHORIZED          body: empty
        - status: INTERNAL_SERVER_ERROR body: json.text = "registry not found"
        - status: INTERNAL_SERVER_ERROR body: json.text = "user not found"
        - status: INTERNAL_SERVER_ERROR body: json.text = "Register with id: {{id}} does not belong to autenticated user"
        - status: INTERNAL_SERVER_ERROR body: json.text = "server error"
    */
    @Transactional
    @CrossOrigin
    @RequestMapping(value =  "/remove/{id}", method = RequestMethod.DELETE)
    public ResponseEntity remove( @RequestHeader("Authorization") String token, @PathVariable("id") long id ){
        
        try{
            if( !token.startsWith("Bearer") )
                return ResponseEntity.status(HttpStatus.UNAUTHORIZED).build();

            token = token.substring(7);

            String username = jwtTokenUtil.getUsernameFromToken(token);

            if( userDetailsService.hasRole(username, "WRITE_ALL_DATA_PRIVILEGE")){

                Optional<Registry> temp = registries.findById(id);
                
                if(temp.isEmpty())
                    return ResponseEntity
                    .status(HttpStatus.INTERNAL_SERVER_ERROR)
                    .body( new TextResponse("registry not found") );
                
                Registry reg = temp.get();
                
                users.findUserByRegistryId(reg.getId()).getRegistry().remove(reg);
                supermarkets.findByRegId(reg.getId()).getRegistries().remove(reg);
                registries.delete(reg);
            
            }else{
                User user = users.findByUsername(username);

                if(user == null )
                    return ResponseEntity
                    .status(HttpStatus.INTERNAL_SERVER_ERROR)
                    .body( new TextResponse("user not found") );
                
                Optional<Registry> temp = registries.findById(id);

                if( temp.isEmpty() )
                    return ResponseEntity
                    .status(HttpStatus.INTERNAL_SERVER_ERROR)
                    .body( new TextResponse("registry not found") );
                
                Registry reg = temp.get();
                
                if(!user.getRegistry().contains(reg))
                    return ResponseEntity
                        .status(HttpStatus.INTERNAL_SERVER_ERROR)
                        .body(new TextResponse("Register with id: "+ id + " does not belong to autenticated user"));
                
                user.getRegistry().remove(reg);
                
                supermarkets.findByRegId(reg.getId()).getRegistries().remove(reg);
                registries.delete(reg);
            }
            
            return ResponseEntity
                    .status(HttpStatus.OK)
                    .body(new TextResponse("removed registry with id "+ id));
            
        }catch(Exception e){
            e.printStackTrace();
            return ResponseEntity
                    .status(HttpStatus.INTERNAL_SERVER_ERROR)
                    .body( new TextResponse("server error") );
        }
        
    }
    
}
