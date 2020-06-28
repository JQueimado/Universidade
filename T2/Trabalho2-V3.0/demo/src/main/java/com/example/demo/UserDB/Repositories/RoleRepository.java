package com.example.demo.UserDB.Repositories;

import com.example.demo.UserDB.Entities.Role;
import org.springframework.data.jpa.repository.JpaRepository;

public interface RoleRepository extends JpaRepository<Role, Long> {
    
    Role findByName(String name);
    
}
