package com.example.Trabalho2V20.DataBase.Repasitories;

import com.example.Trabalho2V20.DataBase.Enteties.User;
import org.springframework.data.repository.CrudRepository;

public interface UserRepository extends CrudRepository<User, Long> {
    
    User findByUsername(String username);
    
}
