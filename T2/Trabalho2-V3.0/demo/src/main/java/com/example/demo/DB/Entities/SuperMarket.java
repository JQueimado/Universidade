package com.example.demo.DB.Entities;

import java.util.Collection;
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
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

@Entity
@Table(name="super")
@Data
@Builder
@AllArgsConstructor
@NoArgsConstructor
public class SuperMarket {
    
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
    
}
