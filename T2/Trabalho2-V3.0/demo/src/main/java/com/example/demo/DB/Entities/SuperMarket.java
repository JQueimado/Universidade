package com.example.demo.DB.Entities;

import java.io.Serializable;
import java.time.LocalDateTime;
import java.time.LocalTime;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.JoinTable;
import javax.persistence.OneToMany;
import javax.persistence.Table;

@Entity
@Table(name="super")
public class SuperMarket implements Serializable {
    
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private long id;
    
    @Column
    private String name; 
    
    @OneToMany(fetch = FetchType.EAGER)
    @JoinTable( 
        name = "super_registrys", 
        joinColumns = @JoinColumn(
          name = "super_id", referencedColumnName = "id"), 
        inverseJoinColumns = @JoinColumn(
          name = "registry_id", referencedColumnName = "id")) 
    private Collection<Registry> registries;

    public SuperMarket(){
        this("");
    }
    
    public SuperMarket( String name) {
        this.name = name;
    }
    
    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }
    
    public String getName(){
        return this.name;
    }
    
    public void setName(String name){
        this.name = name;
    }

    public Collection<Registry> getRegistries() {
        return registries;
    }

    public void setRegistries(Collection<Registry> registries) {
        this.registries = registries;
    }
    
}
