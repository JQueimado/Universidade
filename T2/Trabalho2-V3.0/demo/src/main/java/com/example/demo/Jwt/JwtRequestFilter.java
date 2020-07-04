package com.example.demo.Jwt;

//Codigo Adaptado de https://dzone.com/articles/spring-boot-security-json-web-tokenjwt-hello-world

import com.example.demo.Components.UserDetailsServiceImpl;
import com.example.demo.Exceptions.TokenMissmatchException;
import java.io.IOException;
import javax.servlet.FilterChain;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.authentication.UsernamePasswordAuthenticationToken;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.web.authentication.WebAuthenticationDetailsSource;
import org.springframework.stereotype.Component;
import org.springframework.web.filter.OncePerRequestFilter;
import io.jsonwebtoken.ExpiredJwtException;
import io.jsonwebtoken.MalformedJwtException;

@Component
public class JwtRequestFilter extends OncePerRequestFilter {

    @Autowired
    private UserDetailsServiceImpl jwtUserDetailsService;

    @Autowired
    private JwtTool jwtTokenUtil;

    @Override
    protected void doFilterInternal(HttpServletRequest request, HttpServletResponse response, FilterChain chain)
            throws ServletException, IOException {

        final String requestTokenHeader = request.getHeader("Authorization");
        String username = null;
        String jwtToken = null;

        if (requestTokenHeader != null && requestTokenHeader.startsWith("Bearer ")) {

            jwtToken = requestTokenHeader.substring(7);

            try {

                username = jwtTokenUtil.getUsernameFromToken(jwtToken);

                if (!jwtUserDetailsService.verifyToken(jwtToken, username))
                    throw (new TokenMissmatchException());

            } catch (IllegalArgumentException e) {

                System.out.println("Unable to get JWT Token");
                return;

            } catch (ExpiredJwtException e) {

                System.out.println("JWT Token has expired");
                return;

            } catch (MalformedJwtException e) {

                System.out.println("JWT Token Malformed");
                return;

            } catch (TokenMissmatchException e) {

                System.out.println("JWT Token Does not matched the current loged Token");
                response.setStatus(HttpServletResponse.SC_UNAUTHORIZED);
                return;

            }

        } else {

            logger.warn("JWT Token does not begin with Bearer String");

        }

        if (username != null && SecurityContextHolder.getContext().getAuthentication() == null) {

            UserDetails userDetails = this.jwtUserDetailsService.loadUserByUsername(username);

            if (jwtTokenUtil.validateToken(jwtToken, userDetails)) {

                UsernamePasswordAuthenticationToken usernamePasswordAuthenticationToken = new UsernamePasswordAuthenticationToken(
                        userDetails, null, userDetails.getAuthorities());

                usernamePasswordAuthenticationToken

                        .setDetails(new WebAuthenticationDetailsSource().buildDetails(request));

                SecurityContextHolder.getContext().setAuthentication(usernamePasswordAuthenticationToken);

            }

        }

        chain.doFilter(request, response);

    }

}