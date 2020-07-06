package com.trabalho_so2.UserDB.Repositories;

import com.trabalho_so2.UserDB.Entities.Role;
import org.springframework.data.jpa.repository.JpaRepository;

public interface RoleRepository extends JpaRepository<Role, Long> {
    
    Role findByName(String name);
    
}
