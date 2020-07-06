    package com.example.demo.Config;

import com.example.demo.Jwt.JwtAuthenticationEntryPoint;
import com.example.demo.Jwt.JwtRequestFilter;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.http.HttpMethod;
import org.springframework.security.authentication.AuthenticationManager;
import org.springframework.security.config.annotation.authentication.builders.AuthenticationManagerBuilder;
import org.springframework.security.config.annotation.method.configuration.EnableGlobalMethodSecurity;
import org.springframework.security.config.annotation.web.builders.HttpSecurity;
import org.springframework.security.config.annotation.web.configuration.EnableWebSecurity;
import org.springframework.security.config.annotation.web.configuration.WebSecurityConfigurerAdapter;
import org.springframework.security.config.http.SessionCreationPolicy;
import org.springframework.security.core.userdetails.UserDetailsService;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.security.web.authentication.UsernamePasswordAuthenticationFilter;

@Configuration
@EnableWebSecurity
@EnableGlobalMethodSecurity(prePostEnabled = true)
public class WebSecurityConfig extends WebSecurityConfigurerAdapter {

    private final String USER_READ_ROLE = "READ_USER_DATA_PRIVILEGE";
    private final String USER_WRITE_ROLE = "WRITE_USER_DATA_PRIVILEGE";
    
    private final String ADMIN_READ_ROLE = "READ_ALL_DATA_PRIVILEGE";
    private final String ADMIN_WRITE_ROLE = "WRITE_ALL_DATA_PRIVILEGE";
    
    @Autowired
    private JwtAuthenticationEntryPoint jwtAuthenticationEntryPoint;

    @Autowired
    private UserDetailsService jwtUserDetailsService;

    @Autowired
    private JwtRequestFilter jwtRequestFilter;

    @Autowired
    public void configureGlobal(AuthenticationManagerBuilder auth) throws Exception {
        auth.userDetailsService(jwtUserDetailsService).passwordEncoder(passwordEncoder());
    }

    @Bean
    public PasswordEncoder passwordEncoder() {
        return new BCryptPasswordEncoder();
    }

    @Bean
    @Override
    public AuthenticationManager authenticationManagerBean() throws Exception {
        return super.authenticationManagerBean();
    }

    @Override
    protected void configure(HttpSecurity httpSecurity) throws Exception {  

        httpSecurity.csrf().disable()
        .authorizeRequests()
        //User and Login
        .antMatchers(HttpMethod.POST, "/login").permitAll()
        .antMatchers(HttpMethod.POST, "/register").permitAll()
        .antMatchers(HttpMethod.POST, "/logoutUser").hasAuthority(this.USER_WRITE_ROLE)
        .antMatchers(HttpMethod.POST, "/edit/**").hasAuthority(this.ADMIN_WRITE_ROLE)
        //SuperMarkets
        .antMatchers(HttpMethod.GET, "/supermarkets/**").permitAll()
        .antMatchers(HttpMethod.POST, "/supermarkets/add").hasAuthority(ADMIN_WRITE_ROLE)
        .antMatchers(HttpMethod.DELETE, "/supermarkets/remove/**").hasAuthority(ADMIN_WRITE_ROLE)
                
         //Registry
        .antMatchers(HttpMethod.GET, "/registries/all").hasAuthority(ADMIN_READ_ROLE)
        .antMatchers(HttpMethod.POST, "/registries/new").hasAuthority(USER_WRITE_ROLE)
        .antMatchers(HttpMethod.GET,"/registries/user").hasAuthority(USER_READ_ROLE)
        .antMatchers(HttpMethod.DELETE, "/registries/remove/**").hasAnyAuthority(USER_WRITE_ROLE,ADMIN_WRITE_ROLE)

        .anyRequest().authenticated().and()
        .exceptionHandling().authenticationEntryPoint(jwtAuthenticationEntryPoint).and().sessionManagement()
        .sessionCreationPolicy(SessionCreationPolicy.STATELESS);
        
        httpSecurity.addFilterBefore(jwtRequestFilter, UsernamePasswordAuthenticationFilter.class);

    }

}
