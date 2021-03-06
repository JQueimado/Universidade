package com.example.demo;

import com.trabalho_so2.Rest.Controlers.LoginControler;
import com.trabalho_so2.Rest.Controlers.RegistryController;
import com.trabalho_so2.Rest.Controlers.SuperMarketControler;
import com.trabalho_so2.UserDB.Repositories.PrivilegeRepository;
import com.trabalho_so2.UserDB.Repositories.RoleRepository;
import com.trabalho_so2.UserDB.Repositories.UserRepository;
import static org.assertj.core.api.Assertions.assertThat;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;

@SpringBootTest
public class ComponentsTest  {

    // JPA
    @Autowired
    private UserRepository userRepository;
    
    @Autowired
    private RoleRepository roleRepository;
        
    @Autowired
    private PrivilegeRepository privilegeRepository;
    
    // Rest Controlers
    @Autowired
    private LoginControler logincontroler;
    
    @Autowired
    private RegistryController registryController;
    
    @Autowired
    private SuperMarketControler superMarketControler;
    
   
    
    // Standard Context Loader
    @Test
    void contextLoads() {
    }
 
    @Test
    public void controlers_testing_userRepository(){
        assertThat(userRepository).isNotNull();
    }
    
    @Test
    public void controlers_testing_roleRepository(){
        assertThat(roleRepository).isNotNull();
    }
    
    @Test
    public void controlers_testing_privilegeRepository(){
        assertThat(privilegeRepository).isNotNull();
    }
    
    // Login Component
    @Test
    public void controlers_testing_login(){
        assertThat(logincontroler).isNotNull();
    }
    
    // Registry Component
    @Test
    public void controlers_testing_registry(){
        assertThat(registryController).isNotNull();
    }
    
    // Super Market Component
    @Test
    public void controlers_testing_superMarket(){
        assertThat(superMarketControler).isNotNull();
    }
    
}
