package com.example.testSecureRest;

import lombok.extern.slf4j.Slf4j;
import org.springframework.http.ResponseEntity;
import static org.springframework.http.ResponseEntity.notFound;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.bind.annotation.RestControllerAdvice;
import org.springframework.web.context.request.WebRequest;

@RestControllerAdvice
@Slf4j
public class RestExceptionHandler {    
    @ExceptionHandler(value = {SuperMarketNotFoundException.class})
    public ResponseEntity vehicleNotFound(SuperMarketNotFoundException ex, WebRequest request) {
        log.debug("handling VehicleNotFoundException...");
        return notFound().build();
    }
}
