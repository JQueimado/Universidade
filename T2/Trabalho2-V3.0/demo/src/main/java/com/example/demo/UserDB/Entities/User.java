package com.example.demo.UserDB.Entities;

import com.example.demo.DB.Entities.Registry;
import java.util.Collection;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.JoinTable;
import javax.persistence.ManyToMany;
import javax.persistence.OneToMany;
import javax.persistence.Table;

@Entity
@Table(name= "users")
public class User {
    
        // Data
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;
 
    @Column(nullable = false, unique = true)
    private String username;
 
    @Column
    private String password;
    
    @Column
    private String activeToken;
    
    @ManyToMany(fetch = FetchType.EAGER)
    @JoinTable( 
        name = "user_roles", 
        joinColumns = @JoinColumn(
          name = "users_id", referencedColumnName = "id"), 
        inverseJoinColumns = @JoinColumn(
          name = "role_id", referencedColumnName = "id")) 
    private Collection<Role> roles;
    
    @OneToMany
    @JoinTable( 
        name = "user_registry", 
        joinColumns = @JoinColumn(
          name = "users_id", referencedColumnName = "id"), 
        inverseJoinColumns = @JoinColumn(
          name = "registry_id", referencedColumnName = "id")) 
    private Collection<Registry> registries;
   
    // Constructors
    public User(){
        this.username = null;
        this.password = null;
    }
    
    public User(String username, String password) {
        this.username = username;
        this.password = password;
    }
    
    // Geters and Seters
    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public Collection<Role> getRoles() {
        return roles;
    }

    public void setRoles(Collection<Role> roles) {
        this.roles = roles;
    }
    
    public Collection<Registry> getRegistry() {
        return registries;
    }

    public void setRegistry(Collection<Registry> registries) {
        this.registries = registries;
    }

    public String getActiveToken() {
        return activeToken;
    }

    public void setActiveToken(String activeToken) {
        this.activeToken = activeToken;
    }
    
    
   
}
