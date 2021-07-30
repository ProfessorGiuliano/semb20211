package br.edu.ifmt.cba.carrinho.core.usecases.move;

import br.edu.ifmt.cba.carrinho.core.model.Direction;
import br.edu.ifmt.cba.carrinho.core.ports.ESP8266Client;
import lombok.AllArgsConstructor;
import org.springframework.stereotype.Component;

/**
 * @author daohn
 * @since 19/07/2021
 */
@Component
@AllArgsConstructor
public class MoveForwardUseCase implements MoveUseCase {

  private final ESP8266Client client;

  @Override public void handle(Long time) {
    client.doMovement(time, Direction.FORWARD);
  }
}
