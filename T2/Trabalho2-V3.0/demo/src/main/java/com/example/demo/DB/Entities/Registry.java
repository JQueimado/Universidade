package com.example.demo.DB.Entities;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.Table;
import lombok.Data;

@Entity
@Table(name="registry")
public class Registry {
    
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private long id;
    
    @Column
    private int level; 

    // Constructors

    public Registry(){

        this.level = -1;
    }

    public Registry(int level) {
        
        this.level = level;
    }

    // Geters and Seters
    public Long getId() {

        return id;
    }

    public void setId(Long id) {

        this.id = id;
    }

    public int getLevel() {

        return level;
    }

    public void setLevel(int level) {

        this.level = level;
    }

}
