package com.example.demo.UserDB.Entities;

import java.util.Collection;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.ManyToMany;
import javax.persistence.Table;

@Entity
@Table(name="privilege")
public class PrivilegeEntity {
    
    // Data
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;
    
    private String name;
    
    @ManyToMany(mappedBy = "privileges")
    private Collection<RoleEntity> roles;

    //Constructor
    public PrivilegeEntity(){
        
    }
    
    public PrivilegeEntity(String name) {
        this.name = name;
    }
    
    // Geters and Seters
    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Collection<RoleEntity> getRoles() {
        return roles;
    }

    public void setRoles(Collection<RoleEntity> roles) {
        this.roles = roles;
    }
    
}
