package br.edu.ifmt.cba.carrinho.core.ports;

import br.edu.ifmt.cba.carrinho.core.model.Direction;

/**
 * @author daohn
 * @since 19/07/2021
 */
public interface ESP8266Client {

  void doMovement(Long duration, Direction direction);

}
