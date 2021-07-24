package br.edu.ifmt.cba.carrinho.core.usecases.coordinate;

import br.edu.ifmt.cba.carrinho.core.model.SimpleCoordinate;
import br.edu.ifmt.cba.carrinho.core.ports.CoordinateRepository;
import lombok.AllArgsConstructor;
import org.springframework.stereotype.Component;

/**
 * @author daohn
 * @since 24/07/2021
 */
@Component
@AllArgsConstructor
public class CreateCoordinateUseCase {

  private final CoordinateRepository repository;

  public void handle(SimpleCoordinate initialCoordinate, SimpleCoordinate finalCoordinate, Long map) {



  }

}
