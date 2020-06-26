package com.example.demo.UserDB.Repositories;

import com.example.demo.UserDB.Entities.UserEntity;
import org.springframework.data.repository.CrudRepository;

public interface UserRepository extends CrudRepository<UserEntity, Long> {
    
    UserEntity findByUsername(String username);
    
}
