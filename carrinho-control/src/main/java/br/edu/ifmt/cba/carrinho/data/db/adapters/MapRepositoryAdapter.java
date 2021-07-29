package br.edu.ifmt.cba.carrinho.data.db.adapters;

import br.edu.ifmt.cba.carrinho.core.model.Map;
import br.edu.ifmt.cba.carrinho.core.model.MapNotFoundException;
import br.edu.ifmt.cba.carrinho.core.ports.MapRepository;
import br.edu.ifmt.cba.carrinho.data.db.entities.MapEntity;
import br.edu.ifmt.cba.carrinho.data.db.repositories.JpaMapRepository;
import lombok.AllArgsConstructor;
import org.springframework.stereotype.Component;

import java.util.List;
import java.util.Objects;
import java.util.Optional;
import java.util.stream.Collectors;

/**
 * @author daohn
 * @since 24/07/2021
 */
@Component
@AllArgsConstructor
public class MapRepositoryAdapter implements MapRepository {

  private final JpaMapRepository repository;

  @Override public Map create(Map map) {
    Objects.requireNonNull(map, "O Mapa não pode ser nulo");

    repository.save(MapEntity.fromDomain(map));

    return map;
  }

  @Override public Map update(Long id, Map map) {
    Objects.requireNonNull(map, "O Mapa não pode ser nulo");

    var mapEntity = repository.findById(id).orElseThrow(() -> new MapNotFoundException("Mapa não encontrado"));

    mapEntity.setLocality(map.getLocality());
    mapEntity.setOperator(map.getOperator());

    repository.save(mapEntity);

    return mapEntity.toDomain();
  }

  @Override public Optional<Map> findById(Long id) {
    Objects.requireNonNull(id, "Identificador do Mapa não pode ser nulo");

    return this.repository.findById(id).map(MapEntity::toDomain);
  }

  @Override public List<Map> findAll() {
    return this.repository.findAll()
      .stream()
      .map(MapEntity::toDomain)
      .collect(Collectors.toList());
  }

  @Override public void deleteById(Long id) {

    Objects.requireNonNull(id, "Identificador do Mapa não pode ser nulo");

    this.repository.deleteById(id);
  }
}
