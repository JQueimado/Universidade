package com.example.demo.Components;

import com.example.demo.DB.Entities.SuperMarket;
import com.example.demo.DB.Repositories.SuperMarketRepository;
import com.example.demo.UserDB.Entities.Privilege;
import com.example.demo.UserDB.Entities.Role;
import com.example.demo.UserDB.Entities.User;
import com.example.demo.UserDB.Repositories.PrivilegeRepository;
import com.example.demo.UserDB.Repositories.RoleRepository;
import com.example.demo.UserDB.Repositories.UserRepository;
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
    
    @Autowired
    private SuperMarketRepository superRepository;
    
    @Override
    @Transactional
    public void onApplicationEvent(ContextRefreshedEvent event) {
  
        if (alreadySetup)
            return;
        
        // Privileges
        Privilege readAllPrivilege = createPrivilegeIfNotFound("READ_ALL_DATA_PRIVILEGE");
        Privilege writeAllPrivilege = createPrivilegeIfNotFound("WRITE_ALL_DATA_PRIVILEGE");
        Privilege readUserPrivilege = createPrivilegeIfNotFound("READ_USER_DATA_PRIVILEGE");
        Privilege writeUserPrivilege = createPrivilegeIfNotFound("WRITE_USER_DATA_PRIVILEGE");
        
        // Set all privilege to Roles
        List<Privilege> adminPrivileges = Arrays.asList(readAllPrivilege, writeAllPrivilege); 
        
        List<Privilege> userPrivileges = Arrays.asList(readUserPrivilege, writeUserPrivilege );
        
        // Create Roles
        createRoleIfNotFound("ROLE_ADMIN", adminPrivileges);
        createRoleIfNotFound("ROLE_USER", userPrivileges);
      
        if(userRepository.findByUsername("admin") == null){
            // Create Admin User
            Role adminRole = roleRepository.findByName("ROLE_ADMIN");
            Role userRole = roleRepository.findByName("ROLE_USER");
            User admin = new User("admin", passwordEncoder.encode("admin"));

            admin.setRoles(Arrays.asList(adminRole, userRole));
            
            userRepository.save(admin);
        }
 
        SuperMarket temp = new SuperMarket();
        temp.setName("continete");
        
        superRepository.save(temp);
        
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
