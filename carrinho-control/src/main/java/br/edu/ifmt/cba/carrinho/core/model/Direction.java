package br.edu.ifmt.cba.carrinho.core.model;

/**
 * @author daohn
 * @since 19/07/2021
 */
public enum Direction {
  LEFT("L"),
  RIGHT("R"),
  FORWARD("F"),
  BACK("B");

  private final String direction;

  Direction(String direction) {
    this.direction = direction;
  }

  public String getDirection() {
    return direction;
  }

  public static Direction toEnum(String direction) {
    for(Direction value : Direction.values()) {
      if(value.getDirection().equals(direction)) {
        return value;
      }
    }
    throw new IllegalArgumentException("Direction " + direction + " not found.");
  }
}
