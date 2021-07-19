/*=========================================================================================
                        Baú da Eletrônica Componentes Eletrônicos
                              www.baudaeletronica.com.br
                        Integrando sensor ultrassônico ao NodeMcu
===========================================================================================
 
 Pinagem
 * ---------------------    
 * | HC-SC04 | NodeMCU |   
 * ---------------------   
 * |   Vcc   |   5V    |     
 * |   Trig  |   D7    | 
 * |   Echo  |   D8    |   
 * |   Gnd   |   GND   |   */

#include <Ultrasonic.h> // Declaração de biblioteca

Ultrasonic ultrasonic(D7, D8); // Instância chamada ultrasonic com parâmetros (trig,echo)

void setup() { 
  Serial.begin(9600); // Inicio da comunicação serial
}

void loop() {
  Serial.print("Distancia: "); // Escreve texto na tela
  Serial.print(ultrasonic.distanceRead());// distância medida em cm
  Serial.println("cm"); // escreve texto na tela e pula uma linha
  delay(1000); // aguarda 1s 
}
