package com.example.demo.DB.Repositories;

import com.example.demo.DB.Entities.Registry;
import com.example.demo.Rest.Responses.RegistryDetails;
import java.time.LocalDateTime;
import java.util.Collection;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;

public interface RegistryRepository extends JpaRepository<Registry, Long>{
    
    @Query( value = "select id,level,time "
            + "from "
            + "(select name, registry_id "
            +    "from "
            +    "super join super_registrys on id = super_id) "
            + "as super_reg join registry on id=registry_id "
            + "where name= :name and time > :time ",
            nativeQuery = true)
    Collection<Registry> findBySuperIdAndTimeStamp(@Param("name") String name, @Param("time") LocalDateTime time );
    
}
