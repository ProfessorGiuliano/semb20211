package br.edu.ifmt.cba.carrinho.application.api;

import br.edu.ifmt.cba.carrinho.application.api.dtos.ResponseData;
import br.edu.ifmt.cba.carrinho.core.model.Map;
import br.edu.ifmt.cba.carrinho.core.ports.MapService;
import lombok.AllArgsConstructor;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.PutMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;

/**
 * @author daohn
 * @since 29/07/2021
 */
@RestController
@RequestMapping("/map")
@AllArgsConstructor
public class MapRestController {

  private final MapService mapService;

  @PostMapping
  public ResponseEntity<ResponseData<Map>> create(@RequestBody Map map) {

    var createdMap = this.mapService.create(map);

    var response = new ResponseData<Map>()
      .data(createdMap)
      .message("Mapa criado com sucesso");

    return ResponseEntity.ok(response);
  }

  @PutMapping("/{id}")
  public ResponseEntity<ResponseData<Map>> update(@PathVariable Long id, @RequestBody Map map) {

    var updatedMap = this.mapService.update(id, map);

    var response = new ResponseData<Map>()
      .data(updatedMap)
      .message("Mapa atualizado com sucesso");

    return ResponseEntity.ok(response);
  }

  @GetMapping("/{id}")
  public ResponseEntity<ResponseData<Map>> findById(@PathVariable Long id) {

    var map = this.mapService.findById(id);

    var response = new ResponseData<Map>()
      .data(map)
      .message("Consulta realizada com sucesso");

    return ResponseEntity.ok(response);
  }

  @GetMapping
  public ResponseEntity<ResponseData<List<Map>>> findAll() {

    var maps = this.mapService.findAll();

    var response = new ResponseData<List<Map>>()
      .data(maps)
      .message("Consulta realizada com sucesso");

    return ResponseEntity.ok(response);
  }

}
