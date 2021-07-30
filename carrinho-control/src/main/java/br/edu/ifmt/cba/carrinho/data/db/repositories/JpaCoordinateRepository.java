package br.edu.ifmt.cba.carrinho.data.db.repositories;

import br.edu.ifmt.cba.carrinho.data.db.entities.CoordinateEntity;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

/**
 * @author daohn
 * @since 24/07/2021
 */
@Repository
public interface JpaCoordinateRepository extends JpaRepository<CoordinateEntity, Long> {
}
