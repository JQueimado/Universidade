package com.example.testSecureRest;

import java.io.Serializable;
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
@Table(name="super")
@Data
@Builder
@AllArgsConstructor
@NoArgsConstructor
public class SuperMarket implements Serializable {	
    
    @Id	
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id ;	

    @Column
    private String name;
}
