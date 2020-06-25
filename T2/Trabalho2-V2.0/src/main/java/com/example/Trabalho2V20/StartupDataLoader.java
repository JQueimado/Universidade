package com.example.Trabalho2V20;

import com.example.Trabalho2V20.DataBase.Enteties.Privilege;
import com.example.Trabalho2V20.DataBase.Enteties.Role;
import com.example.Trabalho2V20.DataBase.Enteties.User;
import com.example.Trabalho2V20.DataBase.Repasitories.PrivilegeRepository;
import com.example.Trabalho2V20.DataBase.Repasitories.RoleRepository;
import com.example.Trabalho2V20.DataBase.Repasitories.UserRepository;
import java.util.Arrays;
import java.util.Collection;
import java.util.List;
import javax.transaction.Transactional;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.ApplicationListener;
import org.springframework.context.event.ContextRefreshedEvent;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.stereotype.Component;

@Component
public class StartupDataLoader implements ApplicationListener<ContextRefreshedEvent> {
    
    private boolean alreadySetup = false;
    
    @Autowired
    private UserRepository userRepository;
  
    @Autowired
    private RoleRepository roleRepository;
  
    @Autowired
    private PrivilegeRepository privilegeRepository;
  
    @Autowired
    private PasswordEncoder passwordEncoder;
    
    @Override
    @Transactional
    public void onApplicationEvent(ContextRefreshedEvent event) {
  
        if (alreadySetup)
            return;
        
        // Privileges
        Privilege readAllPrivilege = createPrivilegeIfNotFound("READ_ALL_DATA");
        
        Privilege writeAllPrivilege = createPrivilegeIfNotFound("WRITE_ALL_DATA");
  
        Privilege readUserPrivilege = createPrivilegeIfNotFound("READ_USER_DATA");
        
        Privilege writeUserPrivilege = createPrivilegeIfNotFound("WRITE_USER_DATA");
        
        // Set all privilege to Roles
        List<Privilege> adminPrivileges = Arrays.asList(readAllPrivilege, writeAllPrivilege); 
        
        List<Privilege> userPrivileges = Arrays.asList(readUserPrivilege, writeUserPrivilege );
        
        // Create Roles
        createRoleIfNotFound("ADMIN", adminPrivileges);
        createRoleIfNotFound("USER", userPrivileges);
 
        // Create Admin User
        Role adminRole = roleRepository.findByName("ADMIN");
        Role userRole = roleRepository.findByName("USER");
        User admin = new User( "admin", passwordEncoder.encode("admin"));
        
        admin.setRoles(Arrays.asList(adminRole, userRole));
        
        userRepository.save(admin);
 
        alreadySetup = true;
    }
    
    @Transactional
    private Privilege createPrivilegeIfNotFound(String name) {
  
        Privilege privilege = privilegeRepository.findByName(name);
        if (privilege == null) {
            privilege = new Privilege(name);
            privilegeRepository.save(privilege);
        }
        return privilege;
    }
 
    @Transactional
    private Role createRoleIfNotFound(
      String name, Collection<Privilege> privileges) {
  
        Role role = roleRepository.findByName(name);
        if (role == null) {
            role = new Role(name);
            role.setPrivileges(privileges);
            roleRepository.save(role);
        }
        return role;
    }
    
}
