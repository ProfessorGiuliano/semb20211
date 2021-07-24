package br.edu.ifmt.cba.carrinho.core.usecases.map;

import br.edu.ifmt.cba.carrinho.core.model.Map;
import br.edu.ifmt.cba.carrinho.core.ports.MapRepository;
import lombok.AllArgsConstructor;
import org.springframework.stereotype.Component;

/**
 * @author daohn
 * @since 24/07/2021
 */
@Component
@AllArgsConstructor
public class CreateMapUseCase {

  private final MapRepository repository;

  public Map handle(Map map) {
    return repository.create(map);
  }

}
