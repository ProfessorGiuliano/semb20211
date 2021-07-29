package br.edu.ifmt.cba.carrinho.core.usecases.map;

import br.edu.ifmt.cba.carrinho.core.model.Map;
import br.edu.ifmt.cba.carrinho.core.ports.MapRepository;
import lombok.AllArgsConstructor;
import org.springframework.stereotype.Component;

import java.util.List;

/**
 * @author daohn
 * @since 29/07/2021
 */
@Component
@AllArgsConstructor
public class FindAllUseCase {

  private final MapRepository repository;

  public List<Map> handle(Long id) {
    return repository.findAll();
  }

}
