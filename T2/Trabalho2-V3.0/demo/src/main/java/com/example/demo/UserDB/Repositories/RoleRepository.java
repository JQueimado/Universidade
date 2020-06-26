package com.example.demo.UserDB.Repositories;

import com.example.demo.UserDB.Entities.RoleEntity;
import org.springframework.data.repository.CrudRepository;

public interface RoleRepository extends CrudRepository<RoleEntity, Long> {
    
    RoleEntity findByName(String name);
    
}
