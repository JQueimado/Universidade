package com.example.demo.Jwt;

import com.example.demo.Rest.Request.JwtRequest;
import com.example.demo.UserDB.Entities.Privilege;
import com.example.demo.UserDB.Entities.Role;
import com.example.demo.UserDB.Entities.User;
import com.example.demo.UserDB.Repositories.RoleRepository;
import com.example.demo.UserDB.Repositories.UserRepository;
import java.lang.reflect.Array;
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
            User user = uRep.findByUsername(username);
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
		User newUser = new User();
		newUser.setUsername(user.getUsername());
		newUser.setPassword(bcryptEncoder.encode(user.getPassword()));
                
                Role role = rRep.findByName("USER");                
                newUser.setRoles( Arrays.asList( role ) );
                
		uRep.save(newUser);
                return true;
            }
            else
            {
                return false;
            }
	}
        
        @Transactional
        public boolean logoutUser( String username ){
            
            try{
                uRep.findByUsername(username).setActiveToken("");
                return true;
            }catch(Exception e){
                e.printStackTrace();
                return false;
            }
            
        }
        
        @Transactional
        public boolean postAuth( UserDetails user, String token ){
            try{
                User usere = uRep.findByUsername(user.getUsername());
                usere.setActiveToken(token);
                return true;
            }catch(Exception e ){
                e.printStackTrace();
                return false;
            }
            
        }

        public boolean verifyToken(String token, String username){
            return uRep.findByUsername(username).getActiveToken().compareTo(token) == 0;
        }
        
        //AUX methods
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
       
}
