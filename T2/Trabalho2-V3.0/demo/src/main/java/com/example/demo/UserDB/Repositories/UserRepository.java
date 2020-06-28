package com.example.demo.UserDB.Repositories;

import com.example.demo.UserDB.Entities.User;
import org.springframework.data.jpa.repository.JpaRepository;

public interface UserRepository extends JpaRepository<User, Long> {
    
    User findByUsername(String username);
    
}
