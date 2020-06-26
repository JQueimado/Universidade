package com.example.demo.UserDB.Repositories;

import com.example.demo.UserDB.Entities.PrivilegeEntity;
import org.springframework.data.repository.CrudRepository;

public interface PrivilegeRepository extends CrudRepository<PrivilegeEntity, Long> {
    
    PrivilegeEntity findByName(String name);
    
}
