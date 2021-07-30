package br.edu.ifmt.cba.carrinho.application.api;

import br.edu.ifmt.cba.carrinho.core.ports.MoveService;
import br.edu.ifmt.cba.carrinho.application.api.dtos.ResponseData;
import lombok.AllArgsConstructor;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

/**
 * @author daohn
 * @since 19/07/2021
 */
@RestController
@RequestMapping("/move")
@AllArgsConstructor
public class MoveRestController {

  private final MoveService moveService;

  @GetMapping("/forward")
  public ResponseEntity<ResponseData<Object>> forward(@RequestParam("time") Long time) {

    moveService.forward(time);

    return ResponseEntity.ok(null);
  }

  @GetMapping("/back")
  public ResponseEntity<ResponseData<Object>> back(@RequestParam("time") Long time) {

    moveService.back(time);

    return ResponseEntity.ok(null);
  }

  @GetMapping("/left")
  public ResponseEntity<ResponseData<Object>> left(@RequestParam("time")  Long time) {

    moveService.left(time);

    return ResponseEntity.ok(null);
  }

  @GetMapping("/right")
  public ResponseEntity<ResponseData<Object>> right(@RequestParam("time")  Long time) {

    moveService.right(time);

    return ResponseEntity.ok(null);
  }

}
