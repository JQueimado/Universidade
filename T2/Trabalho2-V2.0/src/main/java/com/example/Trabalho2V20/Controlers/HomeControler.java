package com.example.Trabalho2V20.Controlers;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
public class HomeControler {
    
    @GetMapping("/")
    public String registration(Model model) {
        return "index";
    }
    
}
