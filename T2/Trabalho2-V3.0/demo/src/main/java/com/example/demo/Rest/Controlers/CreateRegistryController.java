package com.example.demo.Rest.Controlers;

import com.example.demo.DB.Repositories.SuperMarketRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import static org.springframework.http.ResponseEntity.ok;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/registries", method = RequestMethod.GET)
public class CreateRegistryController {
    
	public @ResponseBody RegistryEntity getData(@RequestParam("data") String registryid){

	   Resgistry i = registry.findOne(registryid);             
	   String level = i.getLevel();

	   return i;
	}
}