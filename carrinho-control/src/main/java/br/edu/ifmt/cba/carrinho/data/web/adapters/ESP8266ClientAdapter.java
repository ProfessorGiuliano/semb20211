package br.edu.ifmt.cba.carrinho.data.web.adapters;

import br.edu.ifmt.cba.carrinho.core.model.Direction;
import br.edu.ifmt.cba.carrinho.core.ports.ESP8266Client;
import lombok.AllArgsConstructor;
import org.springframework.messaging.simp.SimpMessagingTemplate;
import org.springframework.stereotype.Component;

/**
 * @author daohn
 * @since 19/07/2021
 */
@Component
@AllArgsConstructor
public class ESP8266ClientAdapter implements ESP8266Client {

  private final SimpMessagingTemplate simpMessagingTemplate;

  public void doMovement(Long duration, Direction direction) {

    String message = "Duration: " + duration + ", " + "Direction: " + direction;

    System.out.println(message);

    simpMessagingTemplate.convertAndSend("/channel/output-1", message);

  }
}
