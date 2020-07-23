package com.example.Trabalho2V20;

import com.example.Trabalho2V20.DataBase.Enteties.Privilege;
import com.example.Trabalho2V20.DataBase.Enteties.Role;
import com.example.Trabalho2V20.DataBase.Enteties.User;
import com.example.Trabalho2V20.DataBase.Repasitories.RoleRepository;
import com.example.Trabalho2V20.DataBase.Repasitories.UserRepository;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.List;
import javax.transaction.Transactional;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.GrantedAuthority;
import org.springframework.security.core.authority.SimpleGrantedAuthority;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UserDetailsService;
import org.springframework.security.core.userdetails.UsernameNotFoundException;
import org.springframework.stereotype.Service;

@Service("userDetailsService")
@Transactional
public class UDS implements UserDetailsService {
    
    @Autowired
    private UserRepository uRep;
    
    @Autowired
    private RoleRepository rRep;

    // Aux methods
    private List<String> getPrivileges(Collection<Role> roles) {
  
        List<String> privileges = new ArrayList<>();
        List<Privilege> collection = new ArrayList<>();
        for (Role role : roles) {
            collection.addAll(role.getPrivileges());
        }
        for (Privilege item : collection) {
            privileges.add(item.getName());
        }
        return privileges;
    }
 
    private List<GrantedAuthority> getGrantedAuthorities(List<String> privileges) {
        List<GrantedAuthority> authorities = new ArrayList<>();
        for (String privilege : privileges) {
            authorities.add(new SimpleGrantedAuthority(privilege));
        }
        return authorities;
    }
    
    private Collection<? extends GrantedAuthority> getAuthorities(
      Collection<Role> roles) {
  
        return getGrantedAuthorities(getPrivileges(roles));
    }
    
    // UDS Load method
    @Override
    public UserDetails loadUserByUsername(String string) throws UsernameNotFoundException {
       
        User user = uRep.findByUsername(string);
        if (user == null) {
            return new org.springframework.security.core.userdetails.User(
              " ", " ", true, true, true, true, 
              getAuthorities(Arrays.asList(
                rRep.findByName("USER"))));
        }
 
        return new org.springframework.security.core.userdetails.User( 
                user.getUsername(),
                user.getPassword(),
                getAuthorities(user.getRoles()));
    }
    
    
}
