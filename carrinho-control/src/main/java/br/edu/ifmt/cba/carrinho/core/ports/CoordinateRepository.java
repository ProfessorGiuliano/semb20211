package br.edu.ifmt.cba.carrinho.core.ports;

import br.edu.ifmt.cba.carrinho.core.model.Coordinate;

/**
 * @author daohn
 * @since 24/07/2021
 */
public interface CoordinateRepository {
  Coordinate create(Coordinate coordinate);
}
