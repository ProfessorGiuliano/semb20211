package br.edu.ifmt.cba.carrinho.data.db.entities;

import br.edu.ifmt.cba.carrinho.core.model.Map;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.OneToMany;
import javax.persistence.Table;
import java.util.List;

/**
 * @author daohn
 * @since 24/07/2021
 */
@Entity
@Getter @Setter
@Table(name = "MAP")
@NoArgsConstructor
public class MapEntity extends AbstractEntity {

  @Column(name = "locality", unique = true)
  private String locality;

  @Column(name = "operator")
  private String operator;

  @OneToMany(mappedBy = "map")
  private List<CoordinateEntity> coordinates;

  public Map toDomain() {
    var map = new Map();
    map.setId(getId());
    map.setLocality(getLocality());
    map.setOperator(getOperator());
    return map;
  }

  public static MapEntity fromDomain(Map map) {
    var entity = new MapEntity();
    entity.setId(map.getId());

    entity.setLocality(map.getLocality());

    entity.setOperator(map.getOperator());

    return entity;
  }
}
