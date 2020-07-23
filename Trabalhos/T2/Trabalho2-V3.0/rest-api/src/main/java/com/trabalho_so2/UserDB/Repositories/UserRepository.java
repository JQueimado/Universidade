package com.trabalho_so2.UserDB.Repositories;

import com.trabalho_so2.UserDB.Entities.User;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;

public interface UserRepository extends JpaRepository<User, Long> {
    
    User findByUsername(String username);
    
    @Query(value = "select id,username,password,active_token,enabled from users join user_registry on users_id=id where registry_id= :id", nativeQuery = true)
    User findUserByRegistryId(@Param("id") long id);
    
}
