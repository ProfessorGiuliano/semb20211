package br.edu.ifmt.cba.carrinho.data.db.entities;

import lombok.AllArgsConstructor;
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
@AllArgsConstructor @NoArgsConstructor
public class MapEntity extends AbstractEntity {

  @Column(name = "locality", unique = true)
  private String locality;

  @Column(name = "operator")
  private String operator;

  @OneToMany(mappedBy = "map")
  private List<CoordinateEntity> coordinates;

}
