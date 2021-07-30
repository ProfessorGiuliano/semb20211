package br.edu.ifmt.cba.carrinho.core.model;

import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * @author daohn
 * @since 24/07/2021
 */
@Data
@NoArgsConstructor

public class Coordinate {
  private Long id;
  private Map map;
  private SimpleCoordinate finalCoordinate;
  private SimpleCoordinate initialCoordinate;
}
