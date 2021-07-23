package br.edu.ifmt.cba.carrinho.application.adapters;

import br.edu.ifmt.cba.carrinho.core.ports.MoveService;
import br.edu.ifmt.cba.carrinho.core.usecases.move.MoveBackUseCase;
import br.edu.ifmt.cba.carrinho.core.usecases.move.MoveForwardUseCase;
import br.edu.ifmt.cba.carrinho.core.usecases.move.MoveLeftUseCase;
import br.edu.ifmt.cba.carrinho.core.usecases.move.MoveRightUseCase;
import lombok.AllArgsConstructor;
import org.springframework.stereotype.Service;

/**
 * @author daohn
 * @since 19/07/2021
 */
@Service
@AllArgsConstructor
public class MoveAdapter implements MoveService {

  private final MoveBackUseCase moveBackUseCase;
  private final MoveForwardUseCase moveForwardUseCase;
  private final MoveLeftUseCase moveLeftUseCase;
  private final MoveRightUseCase moveRightUseCase;

  @Override public void forward(Long time) {
    moveForwardUseCase.handle(time);
  }

  @Override public void left(Long time) {
    moveLeftUseCase.handle(time);
  }

  @Override public void back(Long time) {
    moveBackUseCase.handle(time);

  }

  @Override public void right(Long time) {
    moveRightUseCase.handle(time);
  }
}
