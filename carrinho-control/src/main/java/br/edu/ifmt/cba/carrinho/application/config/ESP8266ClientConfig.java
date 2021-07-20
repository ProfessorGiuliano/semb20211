package br.edu.ifmt.cba.carrinho.application.config;

import org.springframework.boot.web.client.RestTemplateBuilder;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.web.client.RestTemplate;

/**
 * @author daohn
 * @since 19/07/2021
 */
@Configuration
public class ESP8266ClientConfig {

  @Bean
  public RestTemplate esp8266Client(RestTemplateBuilder builder) {
    return builder.build();
  }

}
