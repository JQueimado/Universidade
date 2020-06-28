package com.example.demo.DB.Repositories;

import com.example.demo.DB.Entities.Registry;
import org.springframework.data.jpa.repository.JpaRepository;

public interface RegistryRepository extends JpaRepository<Registry, Long>{
    
}
