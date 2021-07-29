package br.edu.ifmt.cba.carrinho.core.model;

/**
 * @author daohn
 * @since 29/07/2021
 */
public class MapNotFoundException extends RuntimeException {

  public MapNotFoundException() {
  }

  public MapNotFoundException(String message) {
    super(message);
  }
}
