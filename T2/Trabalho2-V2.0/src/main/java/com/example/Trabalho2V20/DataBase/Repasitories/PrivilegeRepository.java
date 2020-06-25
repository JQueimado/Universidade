package com.example.Trabalho2V20.DataBase.Repasitories;

import com.example.Trabalho2V20.DataBase.Enteties.Privilege;
import org.springframework.data.jpa.repository.JpaRepository;

public interface PrivilegeRepository extends JpaRepository<Privilege, Long> {
    
    Privilege findByName(String name);
    
}
