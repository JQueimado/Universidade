package com.trabalho_so2.DB.Repositories;

import com.trabalho_so2.DB.Entities.SuperMarket;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;

public interface SuperMarketRepository extends JpaRepository<SuperMarket, Long>{
    
    SuperMarket findByName(String name);
    
    @Query(value = "select id,name "
            + "from (select id,name,registry_id "
            +    "from super join super_registrys on super_id=id)"
            +    "as sup_reg "
            + "where registry_id= :id",
            nativeQuery = true)
    SuperMarket findByRegId(@Param("id") long id);
    
}
