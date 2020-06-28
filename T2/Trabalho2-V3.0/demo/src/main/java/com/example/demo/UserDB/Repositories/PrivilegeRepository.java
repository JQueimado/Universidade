package com.example.demo.UserDB.Repositories;

import com.example.demo.UserDB.Entities.Privilege;
import org.springframework.data.jpa.repository.JpaRepository;

public interface PrivilegeRepository extends JpaRepository<Privilege, Long> {
    
    Privilege findByName(String name);
    
}
