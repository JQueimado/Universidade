package com.example.Trabalho2V20.DataBase.Repasitories;

import com.example.Trabalho2V20.DataBase.Enteties.Role;
import org.springframework.data.repository.CrudRepository;

public interface RoleRepository extends CrudRepository<Role, Long> {
    
    Role findByName(String name);
    
}
