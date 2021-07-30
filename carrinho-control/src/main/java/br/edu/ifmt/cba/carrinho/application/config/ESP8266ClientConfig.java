package br.edu.ifmt.cba.carrinho.application.config;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.http.HttpHeaders;
import org.springframework.http.MediaType;
import org.springframework.web.reactive.function.client.WebClient;

/**
 * @author daohn
 * @since 19/07/2021
 */
@Configuration
public class ESP8266ClientConfig {

  private static final String ESP8266_URL = "";

  @Bean
  public WebClient esp8266Client() {
    return WebClient.builder()
      .baseUrl(ESP8266_URL)
      .defaultHeader(HttpHeaders.CONTENT_TYPE, MediaType.APPLICATION_JSON_VALUE)
      .build();
  }

}
