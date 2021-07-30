package br.edu.ifmt.cba.carrinho.core.ports;

import br.edu.ifmt.cba.carrinho.core.model.Map;

import java.util.List;
import java.util.Optional;

/**
 * @author daohn
 * @since 24/07/2021
 */
public interface MapRepository {

  Map create(Map map);
  Map update(Long id, Map map);
  Optional<Map> findById(Long id);
  List<Map> findAll();
  void deleteById(Long id);

}
