package com.example.demo.Jwt;

import com.example.demo.Rest.Request.JwtRequest;
import com.example.demo.Rest.Request.StatusRequest;
import com.example.demo.Rest.Responses.JwtResponse;
import com.example.demo.Rest.Responses.TextResponse;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpMethod;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.security.authentication.AuthenticationManager;
import org.springframework.security.authentication.BadCredentialsException;
import org.springframework.security.authentication.DisabledException;
import org.springframework.security.authentication.UsernamePasswordAuthenticationToken;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestHeader;
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
    
    @RequestMapping(value = "/sayhi", method = RequestMethod.GET)
    public ResponseEntity<?> hi() throws Exception {
        
        return ResponseEntity.ok("hi");
    }
    
    /*Logout*/
    @RequestMapping(value = "/logoutUser", method = RequestMethod.POST)
    public ResponseEntity<?> logoutEndpoint(
            @RequestHeader("Authorization") String token, 
            @RequestBody StatusRequest req ){
        
        if( !token.startsWith("Bearer") )
            return ResponseEntity
                    .status(HttpStatus.UNAUTHORIZED)
                    .header("Access-Control-Allow-Origin","*")
                    .build();
        
        token = token.substring(7);
        
        // Find User that sent the mesage
        String username = jwtTokenUtil.getUsernameFromToken(token);
        
        if( !userDetailsService.logoutUser(username)) 
            return ResponseEntity
                    .status(HttpStatus.INTERNAL_SERVER_ERROR)
                    .header("Access-Control-Allow-Origin","*")
                    .body("LogOutError");
        
        return ResponseEntity
                .status(HttpStatus.OK)
                .header("Access-Control-Allow-Origin","*")
                .build();   
    }
    
    /* Options */
    @RequestMapping(value = "/logoutUser", method = RequestMethod.OPTIONS)
    public ResponseEntity getOption(){
        return ResponseEntity
                .ok()
                .allow(HttpMethod.POST, HttpMethod.OPTIONS, HttpMethod.GET)
                .header("Access-Control-Allow-Headers","Authorization")
                .build();
    }
    
    //AUX
    private ResponseEntity<?> login( JwtRequest authenticationRequest ) throws Exception{
        
        authenticate(authenticationRequest.getUsername(), authenticationRequest.getPassword());

        final UserDetails userDetails = userDetailsService
            .loadUserByUsername(authenticationRequest.getUsername());

        final String token = jwtTokenUtil.generateToken(userDetails);

        if( !userDetailsService.postAuth(userDetails, token) )
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).body("Authentication Error");
        
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
