package com.example.Trabalho2V20.DataBase.Repasitories;

import com.example.Trabalho2V20.DataBase.Enteties.Role;
import org.springframework.data.jpa.repository.JpaRepository;

public interface RoleRepository extends JpaRepository<Role, Long> {
    
    Role findByName(String name);
    
}
