package br.edu.ifmt.cba.carrinho.data.web.adapters;

import br.edu.ifmt.cba.carrinho.core.model.Direction;
import br.edu.ifmt.cba.carrinho.core.ports.ESP8266Client;
import lombok.AllArgsConstructor;
import org.springframework.stereotype.Component;
import org.springframework.web.reactive.function.client.WebClient;

import java.time.Duration;

/**
 * @author daohn
 * @since 19/07/2021
 */
@Component
@AllArgsConstructor
public class ESP8266ClientAdapter implements ESP8266Client {

  private final WebClient esp8266Client;

  private static final Duration REQUEST_TIMEOUT = Duration.ofSeconds(3);

  public void doMovement(Long duration, Direction direction) {

  }
}
