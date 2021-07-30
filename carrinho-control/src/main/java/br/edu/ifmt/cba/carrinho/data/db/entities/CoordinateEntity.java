package br.edu.ifmt.cba.carrinho.data.db.entities;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;
import javax.persistence.Table;

/**
 * @author daohn
 * @since 24/07/2021
 */
@Entity
@Getter @Setter
@Table(name = "COORDINATE")
@AllArgsConstructor @NoArgsConstructor
public class CoordinateEntity extends AbstractEntity {

  @Column(name = "x0")
  private Double initialX;
  @Column(name = "y0")
  private Double initialY;

  @Column(name = "xf")
  private Double finalX;
  @Column(name = "yf")
  private Double finalY;

  @ManyToOne
  @JoinColumn(name = "id_map")
  private MapEntity map;
}
