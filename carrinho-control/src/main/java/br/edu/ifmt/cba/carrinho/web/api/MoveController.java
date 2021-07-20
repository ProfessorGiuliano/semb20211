package br.edu.ifmt.cba.carrinho.web.api;

import br.edu.ifmt.cba.carrinho.core.ports.MoveService;
import br.edu.ifmt.cba.carrinho.web.api.dtos.ResponseData;
import lombok.AllArgsConstructor;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

/**
 * @author daohn
 * @since 19/07/2021
 */
@RestController
@RequestMapping("/move")
@AllArgsConstructor
public class MoveController {

  private final MoveService moveService;

  @GetMapping("/forward/{time}")
  public ResponseEntity<ResponseData<Object>> forward(@PathVariable Long time) {

    moveService.forward(time);

    return ResponseEntity.ok(null);
  }

  @GetMapping("/back/{time}")
  public ResponseEntity<ResponseData<Object>> back(@PathVariable Long time) {

    moveService.back(time);

    return ResponseEntity.ok(null);
  }

  @GetMapping("/left/{time}")
  public ResponseEntity<ResponseData<Object>> left(@PathVariable Long time) {

    moveService.left(time);

    return ResponseEntity.ok(null);
  }

  @GetMapping("/right/{time}")
  public ResponseEntity<ResponseData<Object>> right(@PathVariable Long time) {

    moveService.right(time);

    return ResponseEntity.ok(null);
  }

}
