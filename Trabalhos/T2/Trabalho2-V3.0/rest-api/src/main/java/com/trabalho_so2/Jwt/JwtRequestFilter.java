package com.trabalho_so2.Jwt;

//Codigo Adaptado de https://dzone.com/articles/spring-boot-security-json-web-tokenjwt-hello-world

import com.trabalho_so2.Jwt.JwtTool;
import com.trabalho_so2.Exceptions.TokenMissmatchException;
import com.trabalho_so2.Components.UserDetailsServiceImpl;
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
import org.springframework.security.core.userdetails.UsernameNotFoundException;

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

                response.setStatus(HttpServletResponse.SC_UNAUTHORIZED);
                response.getWriter().append("Unable to get JWT Token");
                response.getWriter().flush();
                response.getWriter().close();
                return;

            } catch (ExpiredJwtException e) {

                response.setStatus(HttpServletResponse.SC_UNAUTHORIZED);
                response.getWriter().append("JWT Token has expired");
                response.getWriter().flush();
                response.getWriter().close();
                return;

            } catch (MalformedJwtException e) {

                response.setStatus(HttpServletResponse.SC_UNAUTHORIZED);
                response.getWriter().append("JWT Token Malformed");
                response.getWriter().flush();
                response.getWriter().close();
                return;

            } catch (TokenMissmatchException e) {

                response.setStatus(HttpServletResponse.SC_UNAUTHORIZED);
                response.getWriter().append("JWT Token Does not matched the current loged Token");
                response.getWriter().flush();
                response.getWriter().close();
                return;

            } catch(UsernameNotFoundException e){
                
                response.setStatus(HttpServletResponse.SC_UNAUTHORIZED);
                response.getWriter().append(e.getMessage());
                response.getWriter().flush();
                response.getWriter().close();
                return;
            }

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