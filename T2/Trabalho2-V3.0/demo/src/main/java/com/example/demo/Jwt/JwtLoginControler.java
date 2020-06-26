package com.example.demo.Jwt;

import com.example.demo.Rest.Request.JwtRequest;
import com.example.demo.Rest.Responses.JwtResponse;
import com.example.demo.Rest.Responses.TextResponse;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.security.authentication.AuthenticationManager;
import org.springframework.security.authentication.BadCredentialsException;
import org.springframework.security.authentication.DisabledException;
import org.springframework.security.authentication.UsernamePasswordAuthenticationToken;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

@RestController
@CrossOrigin
public class JwtLoginControler{

    @Autowired
    private AuthenticationManager authenticationManager;

    @Autowired
    private JwtTool jwtTokenUtil;

    @Autowired
    private JwtUserDetailsService userDetailsService;

    /* Login endpoint */
    @RequestMapping(value = "/login", method = RequestMethod.POST)
    public ResponseEntity<?> createAuthenticationToken(@RequestBody JwtRequest authenticationRequest) throws Exception {

        return login(authenticationRequest);

    }
    
    /* Register endpoint */
    @RequestMapping(value = "/register", method = RequestMethod.POST)
    public ResponseEntity<?> registerUser(@RequestBody JwtRequest userdto) throws Exception {
        
        // Create new user and send authentication token
        if (userDetailsService.save(userdto) ){
            return login(userdto);
        }
        else{
            return ResponseEntity.ok( new TextResponse("User Alerady Exists", TextResponse.ER_STATUS) );
        }
    }
    
    //AUX
    private ResponseEntity<?> login( JwtRequest authenticationRequest ) throws Exception{
        
        authenticate(authenticationRequest.getUsername(), authenticationRequest.getPassword());

        final UserDetails userDetails = userDetailsService
            .loadUserByUsername(authenticationRequest.getUsername());

        final String token = jwtTokenUtil.generateToken(userDetails);

        return ResponseEntity.ok(new JwtResponse(token));
    }
    
    private void authenticate(String username, String password) throws Exception {

        try {

            authenticationManager.authenticate(new UsernamePasswordAuthenticationToken(username, password));

        } catch (DisabledException e) {

            throw new Exception("USER_DISABLED", e);

        } catch (BadCredentialsException e) {

            throw new Exception("INVALID_CREDENTIALS", e);

        }

    }

}
