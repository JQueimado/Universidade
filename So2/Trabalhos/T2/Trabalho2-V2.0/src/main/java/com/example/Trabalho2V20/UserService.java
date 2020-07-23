package com.example.Trabalho2V20;

import com.example.Trabalho2V20.DataBase.Enteties.Role;
import com.example.Trabalho2V20.DataBase.Enteties.User;
import com.example.Trabalho2V20.DataBase.Repasitories.RoleRepository;
import com.example.Trabalho2V20.DataBase.Repasitories.UserRepository;
import com.example.Trabalho2V20.dto.UserDto;
import java.util.Arrays;
import javax.transaction.Transactional;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.stereotype.Service;

@Service
public class UserService {
    
    @Autowired
    private UserRepository userRepository;
  
    @Autowired
    private RoleRepository roleRepository;
    
    @Autowired
    private PasswordEncoder passwordEncoder;
    
    @Transactional
    public boolean registerNewService( UserDto userData ){
        
        Role userRole = roleRepository.findByName("USER");
        User user = new User( userData.getUsername(), passwordEncoder.encode( userData.getPassword() ) );
        
        user.setRoles( Arrays.asList( userRole ) );
        
        userRepository.save(user);
        return true;
        
    }
    
}
