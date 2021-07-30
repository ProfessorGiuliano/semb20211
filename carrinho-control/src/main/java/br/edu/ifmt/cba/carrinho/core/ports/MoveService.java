package br.edu.ifmt.cba.carrinho.core.ports;

/**
 * @author daohn
 * @since 19/07/2021
 */
public interface MoveService {
  void forward(Long time);
  void left(Long time);
  void back(Long time);
  void right(Long time);
}
