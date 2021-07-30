package br.edu.ifmt.cba.carrinho.application.api.dtos;

import lombok.Data;

/**
 * @author daohn
 * @since 19/07/2021
 */
@Data
public class ResponseData<T> {

  private T data;
  private String message;

  public ResponseData() {}

  public ResponseData<T> data(T data) {
    this.data = data;
    return this;
  }

  public ResponseData<T> message(String message) {
    this.message = message;
    return this;
  }

}
