package com.example.Trabalho2V20.Controlers;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
public class LoginControler {
    
    @GetMapping("/login")
    public String showLogin(){
        return "login";
    }
    
}
