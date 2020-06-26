package com.example.Trabalho2V20.DataBase.Repasitories;

import com.example.Trabalho2V20.DataBase.Enteties.Privilege;
import org.springframework.data.repository.CrudRepository;

public interface PrivilegeRepository extends CrudRepository<Privilege, Long> {
    
    Privilege findByName(String name);
    
}
