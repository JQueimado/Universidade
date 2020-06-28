package com.example.demo.Rest.Controlers;

import com.example.demo.DB.Repositories.SuperMarketRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import static org.springframework.http.ResponseEntity.ok;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/supermarkets", method = RequestMethod.GET)
public class CreateSuperMarketController {
    
	public @ResponseBody SupermarketEntity getData(@RequestParam("data") String supermarketid){

	   Supermaket i = supermarket.findOne(supermarketid);              
	   String supermarket = i.getSuperMarketName();

	   return i;
	}
}