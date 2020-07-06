package com.example.demo.Components;

import com.example.demo.Rest.Request.JwtRequest;
import com.example.demo.Rest.Request.UserDetailsRequest;
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
public class UserDetailsServiceImpl implements UserDetailsService {

	@Autowired
	private UserRepository uRep;
        
        @Autowired
        private RoleRepository rRep;

	@Autowired
	private PasswordEncoder bcryptEncoder;

	@Override
	public UserDetails loadUserByUsername(String username) throws UsernameNotFoundException {
            User user = uRep.findByUsername(username);
            if (user == null || !user.isEnabled()) {
                return new org.springframework.security.core.userdetails.User(
                  " ", " ", true, true, true, true, 
                  getAuthorities(Arrays.asList(
                    rRep.findByName("ROLE_USER"))));
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
                
                Role role = rRep.findByName("ROLE_USER");                
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

        public boolean verifyToken(String token, String username) throws UsernameNotFoundException{
            try{
                User user = uRep.findByUsername(username);

                if(user == null)
                    throw new UsernameNotFoundException("Can not find user "+ username);

                return user.getActiveToken().compareTo(token) == 0;
                
            }catch(Exception e){
                return false;
            }
        }
        
        public boolean hasRole(String username, String role){
            
            Collection<Role> roles = uRep.findByUsername(username).getRoles();
            
            List<String> privileges = new ArrayList();
            
            for( Role current_role: roles){
                for( Privilege current_privilege: current_role.getPrivileges()){
                    privileges.add(current_privilege.getName());
                }
            }
            
            return privileges.contains(role);
        }
        
        @Transactional
        public void edit_user(String username, UserDetailsRequest userdata) throws Exception {
                
            User user = uRep.findByUsername(username);
            
            if( user == null)
                throw new UsernameNotFoundException(username + " not found");
            
            //update data
            user.setUsername(userdata.getUsername());
            user.setPassword(bcryptEncoder.encode( userdata.getPassword() ));
            user.setEnabled(userdata.isStatus());
            user.setActiveToken(""); //logoff if edited
            
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
       
        private boolean status(String username, boolean status){
            
            try{
                
                User user = uRep.findByUsername(username);
                if(user == null)
                    return false;
                
                user.setEnabled(status);
                return true;
                
            }catch(Exception e){
                e.printStackTrace();
                return false;
            }
            
        }
        
}
