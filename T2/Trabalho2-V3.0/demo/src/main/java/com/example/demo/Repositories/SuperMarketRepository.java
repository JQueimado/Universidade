package com.example.demo.Repositories;

import com.example.demo.Entities.SuperMarket;
import org.springframework.data.jpa.repository.JpaRepository;

public interface SuperMarketRepository extends JpaRepository<SuperMarket, Long>{
    
}
