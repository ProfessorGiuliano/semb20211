package br.edu.ifmt.cba.carrinho.data.db.adapters;

import br.edu.ifmt.cba.carrinho.core.model.Map;
import br.edu.ifmt.cba.carrinho.core.ports.MapRepository;
import br.edu.ifmt.cba.carrinho.data.db.repositories.JpaMapRepository;
import lombok.AllArgsConstructor;
import org.springframework.stereotype.Component;

import java.util.Optional;

/**
 * @author daohn
 * @since 24/07/2021
 */
@Component
@AllArgsConstructor
public class MapRepositoryAdapter implements MapRepository {

  private final JpaMapRepository repository;

  @Override public Map create(Map map) {
    return null;
  }

  @Override public Optional<Map> findById(Long id) {
    return Optional.empty();
  }

  @Override public void deleteById(Long id) {

  }
}
