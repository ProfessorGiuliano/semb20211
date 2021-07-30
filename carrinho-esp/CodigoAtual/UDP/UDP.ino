#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Servo.h>
#include <StringSplitter.h>
#include <stdio.h>
#include <stdlib.h>
#include <WiFiUdp.h>
/**
  Definições
**/
//Mudar na linha 91 o ip do Servidor/PC/Receptor
#define nome "nome do wifi"
#define senha "senha do wifi"
#define porta 5050

/**
  Pinos
**/
#define servoPin 2
#define triggerPin 9
#define echoPin 10
#define sdaPin 4
#define sclPin 5
#define motorA1 12
#define motorA2 13
#define motorB1 14
#define motorB2 15


const char* wlan_ssid             = nome;
const char* wlan_password         = senha;

long tempo;
int distancia;

Servo servo;
WiFiUDP udp;
char cstr[50];
String req = "";


void setup() {
  // setup serial
  Serial.begin(115200);
  // flush it - ESP Serial seems to start with rubbish
  Serial.println();

  // connect to WiFi
  Serial.println("Conectando ao wifi.");
  WiFi.begin(wlan_ssid, wlan_password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Conectado.");

  //Configurando os pinos
  servo.attach(servoPin);
  servo.write(0);
  udp.begin(porta);

  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);
  
}
void listen() {
  if (udp.parsePacket() > 0) {
    req = "";
    while (udp.available() > 0) {
      char z = udp.read();
      req += z;
    }
    entrada(req);
  }
}

void loop() {
  listen();
}

void enviar(String msg) {
  String sMsgTemp = msg;
  sMsgTemp.toCharArray(cstr, 50);
  udp.beginPacket("000.000.000.000", porta);//IP do servidor
  udp.println(cstr);
  udp.endPacket();
  Serial.print("Enviando: "); Serial.println(sMsgTemp);
}

void entrada(String msg) {
  String comando[5];

  StringSplitter *splitter = new StringSplitter(msg, '/', 5);  // new StringSplitter(string_to_split, delimiter, limit)
  int itemCount = splitter->getItemCount();

  for (int i = 0; i < itemCount; i++) {
    comando[i] = splitter->getItemAtIndex(i);
  }

  Serial.println("Comando recebido: " + msg);
  msg = "";

  if (comando[0] == "movimento") {
    passo(comando[1], comando[2].toInt());
  } else if (comando[1] == "leitura") {
    leitura();
  }
  hold(100);
}

void passo(String dir, int tempo) {
  dir.toCharArray(cstr, 1);
  switch (cstr[0]) {
    case 'f':
      frenteOn();
      hold(tempo);
      direcaoOFF();
      break;
    case 'r':
      reOn();
      hold(tempo);
      direcaoOFF();
      break;
    case 'd':
      direitaOn();
      hold(tempo);
      direcaoOFF();
      break;
    case 'e':
      esquerdaOn();
      hold(tempo);
      direcaoOFF();
      break;
  }
}
void leitura() {
  String msg = "";
  for (int i = 15; i <= 165; i++) {
    servo.write(i);
    delay(30);
    distancia = calculoDistancia();
    msg += i;
    msg += ",";
    msg += distancia;
    msg += ".";
    enviar(msg);
    msg = "";
  }
  for (int i = 165; i > 15; i--) {
    servo.write(i);
    delay(30);
    distancia = calculoDistancia();
    msg += i;
    msg += ",";
    msg += distancia;
    msg += ".";
    enviar(msg);
    msg = "";
  }
}
void frenteOn() {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
}
void reOn() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
}
void direitaOn() {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
}
void esquerdaOn() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
}
void direcaoOFF() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);
}
int calculoDistancia() {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  tempo = pulseIn(echoPin, HIGH);
  distancia = tempo * 0.034 / 2;
  return distancia;
}
void hold(const unsigned int &ms) {
  // Non blocking hold
  unsigned long m = millis();
  while (millis() - m < ms) {
    yield();
  }
}
