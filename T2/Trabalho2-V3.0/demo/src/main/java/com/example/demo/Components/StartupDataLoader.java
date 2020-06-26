package com.example.demo.Components;

import com.example.demo.DB.Entities.SuperMarket;
import com.example.demo.DB.Repositories.SuperMarketRepository;
import com.example.demo.UserDB.Entities.PrivilegeEntity;
import com.example.demo.UserDB.Entities.RoleEntity;
import com.example.demo.UserDB.Entities.UserEntity;
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
        PrivilegeEntity readAllPrivilege = createPrivilegeIfNotFound("READ_ALL_DATA");
        
        PrivilegeEntity writeAllPrivilege = createPrivilegeIfNotFound("WRITE_ALL_DATA");
  
        PrivilegeEntity readUserPrivilege = createPrivilegeIfNotFound("READ_USER_DATA");
        
        PrivilegeEntity writeUserPrivilege = createPrivilegeIfNotFound("WRITE_USER_DATA");
        
        // Set all privilege to Roles
        List<PrivilegeEntity> adminPrivileges = Arrays.asList(readAllPrivilege, writeAllPrivilege); 
        
        List<PrivilegeEntity> userPrivileges = Arrays.asList(readUserPrivilege, writeUserPrivilege );
        
        // Create Roles
        createRoleIfNotFound("ADMIN", adminPrivileges);
        createRoleIfNotFound("USER", userPrivileges);
      
        if(userRepository.findByUsername("admin") == null){
            // Create Admin User
            RoleEntity adminRole = roleRepository.findByName("ADMIN");
            RoleEntity userRole = roleRepository.findByName("USER");
            UserEntity admin = new UserEntity("admin", passwordEncoder.encode("admin"));

            admin.setRoles(Arrays.asList(adminRole, userRole));
            
            userRepository.save(admin);
        }
 
        SuperMarket temp = new SuperMarket();
        temp.setName("continete");
        
        superRepository.save(temp);
        
        alreadySetup = true;
    }
    
    @Transactional
    private PrivilegeEntity createPrivilegeIfNotFound(String name) {
  
        PrivilegeEntity privilege = privilegeRepository.findByName(name);
        if (privilege == null) {
            privilege = new PrivilegeEntity(name);
            privilegeRepository.save(privilege);
        }
        return privilege;
    }
 
    @Transactional
    private RoleEntity createRoleIfNotFound(
      String name, Collection<PrivilegeEntity> privileges) {
  
        RoleEntity role = roleRepository.findByName(name);
        if (role == null) {
            role = new RoleEntity(name);
            role.setPrivileges(privileges);
            roleRepository.save(role);
        }
        return role;
    }

}
