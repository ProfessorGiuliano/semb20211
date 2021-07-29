package br.edu.ifmt.cba.carrinho.core.ports;

import br.edu.ifmt.cba.carrinho.core.model.Map;

import java.util.List;

/**
 * @author daohn
 * @since 29/07/2021
 */
public interface MapService {
  Map create(Map map);
  Map update(Long id, Map map);
  Map findById(Long id);
  List<Map> findAll();
  void deleteById(Long id);
}
