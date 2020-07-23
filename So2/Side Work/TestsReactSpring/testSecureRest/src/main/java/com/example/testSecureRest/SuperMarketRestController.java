package com.example.testSecureRest;

import javax.servlet.http.HttpServletRequest;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import static org.springframework.http.ResponseEntity.created;
import static org.springframework.http.ResponseEntity.noContent;
import static org.springframework.http.ResponseEntity.ok;
import org.springframework.web.bind.annotation.DeleteMapping;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.PutMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.servlet.support.ServletUriComponentsBuilder;

@RestController
@RequestMapping("/supermarkets")
public class SuperMarketRestController {    
    
    @Autowired
    private SuperMarketRepository vehicles;    
    
    public SuperMarketRestController(SuperMarketRepository vehicles) {
        this.vehicles = vehicles;
    }

    @GetMapping("")
    public ResponseEntity all() {
        return ok(this.vehicles.findAll());
    }    
    
    @PostMapping("")
    public ResponseEntity save(@RequestBody SuperMarketForm form, HttpServletRequest request) {
        SuperMarket saved = this.vehicles.save(SuperMarket.builder().name(form.getName()).build());
        return created(
            ServletUriComponentsBuilder
                .fromContextPath(request)
                .path("/supermarkets/{id}")
                .buildAndExpand(saved.getId())
                .toUri())
            .build();
    }    
    
    @GetMapping("/{id}")
    public ResponseEntity get(@PathVariable("id") Long id) {
        return ok(this.vehicles.findById(id).orElseThrow(() -> new SuperMarketNotFoundException()));
    }
    
    @PutMapping("/{id}")
    public ResponseEntity update(@PathVariable("id") Long id, @RequestBody SuperMarketForm form) {
        SuperMarket existed = this.vehicles.findById(id).orElseThrow(() -> new SuperMarketNotFoundException());
        existed.setName(form.getName());        this.vehicles.save(existed);
        return noContent().build();
    }    
    
    @DeleteMapping("/{id}")
    public ResponseEntity delete(@PathVariable("id") Long id) {
        SuperMarket existed = this.vehicles.findById(id).orElseThrow(() -> new SuperMarketNotFoundException());
        this.vehicles.delete(existed);
        return noContent().build();
    }
}