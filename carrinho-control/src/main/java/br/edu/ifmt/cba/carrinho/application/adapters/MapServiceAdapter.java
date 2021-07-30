package br.edu.ifmt.cba.carrinho.application.adapters;

import br.edu.ifmt.cba.carrinho.core.model.Map;
import br.edu.ifmt.cba.carrinho.core.ports.MapService;
import br.edu.ifmt.cba.carrinho.core.usecases.map.CreateMapUseCase;
import br.edu.ifmt.cba.carrinho.core.usecases.map.DeleteMapUseCase;
import br.edu.ifmt.cba.carrinho.core.usecases.map.FindAllUseCase;
import br.edu.ifmt.cba.carrinho.core.usecases.map.FindByIdUseCase;
import br.edu.ifmt.cba.carrinho.core.usecases.map.UpdateMapUseCase;
import lombok.AllArgsConstructor;
import org.springframework.stereotype.Component;

import java.util.List;

/**
 * @author daohn
 * @since 29/07/2021
 */
@Component
@AllArgsConstructor
public class MapServiceAdapter implements MapService {

  private final CreateMapUseCase createMapUseCase;
  private final UpdateMapUseCase updateMapUseCase;
  private final FindByIdUseCase findByIdUseCase;
  private final FindAllUseCase findAllUseCase;
  private final DeleteMapUseCase deleteMapUseCase;

  @Override public Map create(Map map) {
    return this.createMapUseCase.handle(map);
  }

  @Override public Map update(Long id, Map map) {
    return this.updateMapUseCase.handle(id, map);
  }

  @Override public Map findById(Long id) {
    return this.findByIdUseCase.handle(id);
  }

  @Override public List<Map> findAll() {
    return this.findAllUseCase.handle();
  }

  @Override public void deleteById(Long id) {
    this.deleteMapUseCase.handle(id);
  }
}
