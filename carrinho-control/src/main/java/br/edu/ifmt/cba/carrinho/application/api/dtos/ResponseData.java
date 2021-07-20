package br.edu.ifmt.cba.carrinho.application.api.dtos;

import lombok.Builder;
import lombok.Data;

/**
 * @author daohn
 * @since 19/07/2021
 */
@Data
@Builder
public class ResponseData<T> {

  private T data;
  private String message;

}
