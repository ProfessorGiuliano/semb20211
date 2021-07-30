package br.edu.ifmt.cba.carrinho.data.db.entities;

import lombok.Getter;
import lombok.RequiredArgsConstructor;
import lombok.Setter;
import lombok.ToString;
import org.hibernate.Hibernate;
import org.springframework.data.annotation.CreatedDate;

import javax.persistence.Column;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.MappedSuperclass;
import java.io.Serializable;
import java.time.LocalDateTime;
import java.util.Objects;

/**
 * @author daohn
 * @since 24/07/2021
 */
@Getter @Setter @ToString @RequiredArgsConstructor
@MappedSuperclass
public abstract class AbstractEntity implements Serializable {

  @Id
  @Column(name = "id")
  @GeneratedValue(strategy = GenerationType.IDENTITY)
  private Long id;

  @CreatedDate
  @Column(name = "created_at")
  private LocalDateTime createdAt;

  @Override
  public boolean equals(Object o) {
    if(this == o) return true;
    if(o == null || Hibernate.getClass(this) != Hibernate.getClass(o)) return false;
    AbstractEntity that = (AbstractEntity) o;

    return Objects.equals(id, that.id);
  }

  @Override
  public int hashCode() {
    return 2076924755;
  }
}
