package br.edu.ifmt.cba.carrinho.application.api;

import lombok.AllArgsConstructor;
import org.springframework.messaging.handler.annotation.MessageMapping;
import org.springframework.messaging.handler.annotation.Payload;
import org.springframework.messaging.handler.annotation.SendTo;
import org.springframework.stereotype.Controller;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

/**
 * @author daohn
 * @since 22/07/2021
 */
@Controller
@AllArgsConstructor
public class ESP8266CommunicationController {

  @MessageMapping("/input")
  @SendTo("/channel/output-2")
  public String getMessages(@Payload String message){
    var date = LocalDateTime.now().format(DateTimeFormatter.ofPattern("dd/MM/yyyy HH:mm:ss"));
    var saida = date + " - " + message;
    System.out.println(saida);
    return saida;
  }

}
