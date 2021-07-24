package br.edu.ifmt.cba.carrinho.data.db.adapters;

import br.edu.ifmt.cba.carrinho.core.model.Coordinate;
import br.edu.ifmt.cba.carrinho.core.ports.CoordinateRepository;
import lombok.AllArgsConstructor;
import org.springframework.stereotype.Component;

/**
 * @author daohn
 * @since 24/07/2021
 */
@Component
@AllArgsConstructor
public class CoordinateRepositoryAdapter implements CoordinateRepository {

  private final CoordinateRepository repository;

  @Override public Coordinate create(Coordinate coordinate) {
    return null;
  }
}
