package br.edu.ifmt.cba.carrinho.core.usecases.map;

import br.edu.ifmt.cba.carrinho.core.model.Map;
import br.edu.ifmt.cba.carrinho.core.ports.MapRepository;
import lombok.AllArgsConstructor;
import org.springframework.stereotype.Component;

/**
 * @author daohn
 * @since 29/07/2021
 */
@Component
@AllArgsConstructor
public class UpdateMapUseCase {

  private final MapRepository repository;

  public Map handle(Long id, Map map) {
    return repository.update(id, map);
  }

}
