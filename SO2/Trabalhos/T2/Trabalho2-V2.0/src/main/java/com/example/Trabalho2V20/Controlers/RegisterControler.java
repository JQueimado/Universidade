package com.example.Trabalho2V20.Controlers;

import com.example.Trabalho2V20.DataBase.Enteties.Role;
import com.example.Trabalho2V20.DataBase.Enteties.User;
import com.example.Trabalho2V20.DataBase.Repasitories.RoleRepository;
import com.example.Trabalho2V20.DataBase.Repasitories.UserRepository;
import com.example.Trabalho2V20.UserService;
import com.example.Trabalho2V20.dto.UserDto;
import java.util.Arrays;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.validation.Errors;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.context.request.WebRequest;
import org.springframework.web.servlet.ModelAndView;

@Controller
public class RegisterControler {
    
    @Autowired
    private UserService uService;
    
    @GetMapping( value = "/register" )
    public String showRegister(WebRequest request, Model model){
        UserDto user = new UserDto();
        model.addAttribute("user", user);
        return "register";
    }
    
    @PostMapping( value="/addUser" )
    public String registerUser(@ModelAttribute("user") UserDto userData){
        System.out.println("register post");
        uService.registerNewService(userData);
        return "redirect:/";
    }
    
}
