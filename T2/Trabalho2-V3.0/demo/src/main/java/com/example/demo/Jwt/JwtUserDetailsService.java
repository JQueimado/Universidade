package com.example.demo.Jwt;

import com.example.demo.UserDB.Entities.PrivilegeEntity;
import com.example.demo.UserDB.Entities.RoleEntity;
import com.example.demo.UserDB.Entities.UserEntity;
import com.example.demo.UserDB.Repositories.RoleRepository;
import com.example.demo.UserDB.Repositories.UserRepository;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.GrantedAuthority;
import org.springframework.security.core.authority.SimpleGrantedAuthority;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UserDetailsService;
import org.springframework.security.core.userdetails.UsernameNotFoundException;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.stereotype.Service;

@Service("userDetailsService")
public class JwtUserDetailsService implements UserDetailsService {

	@Autowired
	private UserRepository uRep;
        
        @Autowired
        private RoleRepository rRep;

	@Autowired
	private PasswordEncoder bcryptEncoder;

	@Override
	public UserDetails loadUserByUsername(String username) throws UsernameNotFoundException {
            UserEntity user = uRep.findByUsername(username);
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

	public boolean save(JwtRequest user) {
            
            if( uRep.findByUsername(user.getUsername() ) == null ) {
		UserEntity newUser = new UserEntity();
		newUser.setUsername(user.getUsername());
		newUser.setPassword(bcryptEncoder.encode(user.getPassword()));
                
                RoleEntity role = rRep.findByName("USER");                
                newUser.setRoles( Arrays.asList( role ) );
                
		uRep.save(newUser);
                return true;
            }
            else
            {
                return false;
            }
	}

        //AUX methods
        private List<String> getPrivileges(Collection<RoleEntity> roles) {
  
            List<String> privileges = new ArrayList<>();
            
            List<PrivilegeEntity> collection = new ArrayList<>();
            
            for (RoleEntity role : roles) {
                collection.addAll(role.getPrivileges());
            }
            
            for (PrivilegeEntity item : collection) {
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
            Collection<RoleEntity> roles) {

              return getGrantedAuthorities(getPrivileges(roles));
          }
        
}
