package br.edu.ifmt.cba.carrinho.data.web.adapters;

import br.edu.ifmt.cba.carrinho.core.ports.ESP8266Client;
import lombok.AllArgsConstructor;
import org.springframework.stereotype.Component;
import org.springframework.web.client.RestTemplate;

/**
 * @author daohn
 * @since 19/07/2021
 */
@Component
@AllArgsConstructor
public class ESP8266ClientAdapter implements ESP8266Client {

  private final RestTemplate esp8266Client;





}
