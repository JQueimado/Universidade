package com.example.testSecureRest;

import org.springframework.data.jpa.repository.JpaRepository;

public interface SuperMarketRepository extends JpaRepository<SuperMarket, Long> {
}