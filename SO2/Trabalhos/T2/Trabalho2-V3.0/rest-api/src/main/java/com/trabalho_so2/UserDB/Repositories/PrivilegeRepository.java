package com.trabalho_so2.UserDB.Repositories;

import com.trabalho_so2.UserDB.Entities.Privilege;
import org.springframework.data.jpa.repository.JpaRepository;

public interface PrivilegeRepository extends JpaRepository<Privilege, Long> {
    
    Privilege findByName(String name);
    
}
