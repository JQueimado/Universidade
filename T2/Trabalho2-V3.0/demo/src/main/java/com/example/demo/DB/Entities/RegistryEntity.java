package com.example.demo.DB.Entities;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.Table;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

@Entity
@Table(name="registry")
@Data
@Builder
@AllArgsConstructor
@NoArgsConstructor
public class Registry {
    
    @Registry_Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private long registry_id;
    
    @Level
    private String level; 

    @OneToMany(fetch = FetchType.EAGER)
    @JoinTable( 
        name = "super_registry", 
        joinColumns = @JoinColumn(
          name = "registry_id", referencedColumnName = "id"), 
        inverseJoinColumns = @JoinColumn(
          name = "super_id", referencedColumnName = "id")) 
    private Collection<Super_RegistryEntity> ids;

    // Constructors

    public RegistryEntity(){

        this.level = null;
    }

    public RegistryEntity(String level) {
        
        this.level = level;
    }

    // Geters and Seters
    public Long getId() {

        return id;
    }

    public void setId(Long id) {

        this.id = id;
    }

    public String getLevel() {

        return level;
    }

    public void setLevel(String level) {

        this.level = level;
    }

     public Collection<Super_RegistryEntity> getIds() {
        return ids;
    }

    public void setIds(Collection<Super_RegistryEntity> ids) {
        this.ids = ids;
    }

}
