package com.example.demo.DB.Repositories;

import com.example.demo.DB.Entities.SuperMarketEntity;
import org.springframework.data.jpa.repository.JpaRepository;

public interface SuperMarketRepository extends JpaRepository<SuperMarketEntity, Long>{
    
}
