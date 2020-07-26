package com.example.testSecureRest;

import java.util.Arrays;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.CommandLineRunner;
import org.springframework.stereotype.Component;

@Component
@Slf4j
public class DataStarter implements CommandLineRunner {    
    @Autowired
    SuperMarketRepository vehicles;
    
    @Override
    public void run(String... args) throws Exception {
        log.debug("initializing vehicles data...");
        Arrays.asList("continente", "pingodoce").forEach(v -> this.vehicles.saveAndFlush(SuperMarket.builder().name(v).build()));        
        log.debug("printing all vehicles...");
        this.vehicles.findAll().forEach(v -> log.debug(" Vehicle :" + v.toString()));
    }
}
