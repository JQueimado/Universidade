package com.trabalho_so2.Rest.Controlers;

import com.trabalho_so2.Components.UserDetailsServiceImpl;
import com.trabalho_so2.Jwt.JwtTool;
import com.trabalho_so2.Rest.Request.JwtRequest;
import com.trabalho_so2.Rest.Request.StatusRequest;
import com.trabalho_so2.Rest.Request.UserDetailsRequest;
import com.trabalho_so2.Rest.Responses.JwtResponse;
import com.trabalho_so2.Rest.Responses.TextResponse;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.security.authentication.AuthenticationManager;
import org.springframework.security.authentication.BadCredentialsException;
import org.springframework.security.authentication.DisabledException;
import org.springframework.security.authentication.UsernamePasswordAuthenticationToken;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestHeader;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

@RestController
@CrossOrigin
public class LoginControler{

    @Autowired
    private AuthenticationManager authenticationManager;

    @Autowired
    private JwtTool jwtTokenUtil;

    @Autowired
    private UserDetailsServiceImpl userDetailsService;

    /* Login endpoint
    path : /login
    method: POST
    expected body: json.username.String, json.password.String
    responses:
        - status: OK            body: json.token = generated token
        - status: UNAUTHORIZED  body: json.text = "Authetiction Error"
    */
    @CrossOrigin
    @RequestMapping(value = "/login", method = RequestMethod.POST)
    public ResponseEntity<?> createAuthenticationToken(@RequestBody JwtRequest authenticationRequest) throws Exception {

        return login(authenticationRequest);

    }
    
    /* Register endpoint
    path : /register
    method: POST
    expected body: json.username.String, json.password.String
    responses:
        - status: OK            body: json.token = generated token
        - status: UNAUTHORIZED  body: json.text = "Authetiction Error"
        - status: BAD_REQUEST   body: json.text = "User Alerady Exists"
    */
    @CrossOrigin
    @RequestMapping(value = "/register", method = RequestMethod.POST)
    public ResponseEntity<?> registerUser(@RequestBody JwtRequest userdto) throws Exception {
        
        // Create new user and send authentication token
        if (userDetailsService.save(userdto) ){
            return login(userdto);
        }
        else{
            return ResponseEntity.status(HttpStatus.BAD_REQUEST).body( new TextResponse("User Alerady Exists") );
        }
    }
    
    /*Logout
    path : /logoutUser
    method: POST
    expected body: indiferent
    responses:
        - status: OK                    body: json.text = "sucssesfuly logedout"
        - status: UNAUTHORIZED          body: json.text = "token doesnt start with Bearer"
        - status: INTERNAL_SERVER_ERROR body: json.text = "LogOutError"
    */
    @CrossOrigin
    @RequestMapping(value = "/logoutUser", method = RequestMethod.POST)
    public ResponseEntity<?> logoutEndpoint(
            @RequestHeader("Authorization") String token, 
            @RequestBody StatusRequest req ){
        
        if( !token.startsWith("Bearer") )
            return ResponseEntity
                    .status(HttpStatus.UNAUTHORIZED)
                    .body(new TextResponse("token doesnt start with Bearer"));
        
        token = token.substring(7);
        
        // Find User that sent the mesage
        String username = jwtTokenUtil.getUsernameFromToken(token);
        
        if( !userDetailsService.logoutUser(username)) 
            return ResponseEntity
                    .status(HttpStatus.INTERNAL_SERVER_ERROR)
                    .body(new TextResponse("LogOutError"));
        
        return ResponseEntity
                .status(HttpStatus.OK)
                .body( new TextResponse( "sucssesfuly logedout" ));   
    }
    
    /*Edit User
    path : /edit/{name}
    method: POST
    expected body: json.username.String, json.password.String, json.status.boolean
    responses:
        - status: OK                    body: json.text = "User {{name}} edited"
        - status: INTERNAL_SERVER_ERROR body: json.text = "Server Error"
    */
    @CrossOrigin
    @RequestMapping(value = "/edit/{name}", method = RequestMethod.POST)
    public ResponseEntity edit_User(
            @RequestBody UserDetailsRequest request,
            @PathVariable("name") String name ){
        
        try{
            userDetailsService.edit_user(name, request);
            return ResponseEntity
                    .status(HttpStatus.OK)
                    .body(new TextResponse("User "+ name + " edited" ));
        }catch(Exception e){
            e.printStackTrace();
            return ResponseEntity
                    .status(HttpStatus.INTERNAL_SERVER_ERROR)
                    .body(new TextResponse("Server Error"));
        }
        
    }
    
    //AUX
    private ResponseEntity<?> login( JwtRequest authenticationRequest ) throws Exception{
        
        authenticate(authenticationRequest.getUsername(), authenticationRequest.getPassword());

        final UserDetails userDetails = userDetailsService
            .loadUserByUsername(authenticationRequest.getUsername());

        final String token = jwtTokenUtil.generateToken(userDetails);

        if( !userDetailsService.postAuth(userDetails, token) )
            return ResponseEntity.status(HttpStatus.UNAUTHORIZED).body(new TextResponse( "Authentication Error" ));
        
        return ResponseEntity.status(HttpStatus.OK).body(new JwtResponse(token));
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
