package com.trabalho_so2.Rest.Controlers;

import com.trabalho_so2.DB.Entities.Registry;
import com.trabalho_so2.DB.Entities.SuperMarket;
import com.trabalho_so2.DB.Repositories.RegistryRepository;
import com.trabalho_so2.DB.Repositories.SuperMarketRepository;
import com.trabalho_so2.Rest.Request.SuperMarketRequest;
import com.trabalho_so2.Rest.Responses.SuperMarketResponse;
import com.trabalho_so2.Rest.Responses.TextResponse;
import com.trabalho_so2.UserDB.Repositories.UserRepository;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import javax.transaction.Transactional;
import jdk.jfr.internal.RequestEngine;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpMethod;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import static org.springframework.http.ResponseEntity.ok;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/supermarkets")
public class SuperMarketControler {
    
    @Autowired
    private SuperMarketRepository supermarkets;
   
    @Autowired
    private RegistryRepository registies;
    
    @Autowired UserRepository users;
    
    //Get All Super Markets
    @GetMapping("/{time}")
    public ResponseEntity all( @PathVariable("time") long time ) {
        
        //Time Check
        if( time < 0 )
            return ResponseEntity
                .status(HttpStatus.BAD_REQUEST)
                .header("Access-Control-Allow-Origin","*")
                .body(new TextResponse("invalid time: "+time));
        
        Collection<SuperMarket> supers = supermarkets.findAll();
        List<SuperMarketResponse> to_send = new ArrayList<>();
        
        for( SuperMarket s: supers){
            
            SuperMarketResponse temp = new SuperMarketResponse();
            temp.setSuper_name(s.getName());
            Collection<Registry> valid_reistries = registies.findBySuperIdAndTimeStamp(s.getName(), LocalDateTime.now().minusHours(time));
            
            for(Registry r: valid_reistries){
                temp.add( r.getLevel() );
                
            }
            
            to_send.add(temp);
            
        }
        
        return ResponseEntity
                .status(HttpStatus.OK)
                .header("Access-Control-Allow-Origin","*")
                .body(to_send);
    }    
    
    //Options Handler
    /*
    @RequestMapping( value = "", method = RequestMethod.OPTIONS)
    public ResponseEntity getOption(){
        return ResponseEntity.ok().allow(HttpMethod.POST, HttpMethod.OPTIONS, HttpMethod.GET).header("Access-Control-Allow-Headers","Authorization").build();
    }
    */

    //Create Handler
    @RequestMapping( value = "/add", method = RequestMethod.POST)
    public ResponseEntity addSuperMarket( @RequestBody SuperMarketRequest request ){
        try{
            
            SuperMarket eval = supermarkets.findByName(request.getName());
            
            if( eval != null){
                return ResponseEntity
                        .status(HttpStatus.CONFLICT)
                        .header("Access-Control-Allow-Headers","Authorization")
                        .body(new TextResponse("supermarket already exists"));
            }
            
            SuperMarket nsp = new SuperMarket();
            nsp.setName(request.getName());
            
            supermarkets.save(nsp);

            return ResponseEntity
                    .status(HttpStatus.OK)
                    .header("Access-Control-Allow-Headers","Authorization")
                    .body(new TextResponse("created "+ request.getName()));
            
        }catch( Exception e){
            return ResponseEntity
                    .status(HttpStatus.INTERNAL_SERVER_ERROR)
                    .header("Access-Control-Allow-Headers","Authorization")
                    .body("server error");
        }
    }
    
    @Transactional
    @RequestMapping( value = "/remove/{name}", method = RequestMethod.DELETE)
    public ResponseEntity removeSuperMarquet( @PathVariable("name") String name ){
        
        try
        {   
            SuperMarket toDel = supermarkets.findByName(name);
            
            if(toDel == null)
                return ResponseEntity
                    .status(HttpStatus.OK)
                    .header("Access-Control-Allow-Headers","Authorization")
                    .body(new TextResponse("Supermarket called  "+ name +" des not exist"));
            
            // Delete Registries
            List<Registry> temp = new ArrayList<>();
            
            for( Registry reg: toDel.getRegistries() ){
                
                users.findUserByRegistryId(reg.getId()).getRegistry().remove(reg);
                temp.add(reg);
            }
                
            supermarkets.delete(toDel);
            
            for(Registry reg: temp){
                registies.delete(reg);
            }
            
            return ResponseEntity
                    .ok()
                    .header("Access-Control-Allow-Headers","Authorization")
                    .body(new TextResponse("removed "+name+" and all its registries"));
            
        }
        catch(Exception e )
        {
            e.printStackTrace();
            return ResponseEntity
                    .status(HttpStatus.INTERNAL_SERVER_ERROR)
                    .header("Access-Control-Allow-Headers","Authorization")
                    .body(new TextResponse("server error"));
        }
        
    }
    
}
