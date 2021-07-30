#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "WebSocketsClient.h"
#include "StompClient.h"
#include <Servo.h>
#include <StringSplitter.h>
#include <stdio.h>
#include <stdlib.h>
/**
  Definições
**/

#define nome "nome do wifi"
#define senha "senha do wifi"
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

long tempo;
int distancia;
char cstr[50];
const char* wlan_ssid             = nome;
const char* wlan_password         = senha;
String req = "";
bool useWSS                       = true;
const char* ws_host               = "000.000.000.000";//IP do servidor
const int ws_port                 = 8080;
const char* ws_baseurl            = "/ws/"; // don't forget leading and trailing "/" !!!

Servo servo;
WebSocketsClient webSocket;

Stomp::StompClient stomper(webSocket, ws_host, ws_port, ws_baseurl, true);


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
  servo.attach(servoPin);
  servo.write(0);
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);
  stomper.onConnect(subscribe);
  stomper.onError(error);
  stomper.begin();
}

void subscribe(Stomp::StompCommand cmd) {
  Serial.println("Connected to STOMP broker");
  stomper.subscribe("/channel/output-1", Stomp::CLIENT, handleSampleMessage);
}

void error(const Stomp::StompCommand cmd) {
  Serial.println("ERROR: " + cmd.body);
}
Stomp::Stomp_Ack_t handleSampleMessage(const Stomp::StompCommand cmd) {
  Serial.print("Msg recebida: ");
  req = cmd.body;
  Serial.println(req);
  entrada(req);
  return Stomp::CONTINUE;
}

void loop() {
  webSocket.loop();
}
void enviar(String msg) {
  stomper.sendMessage("/server/input", msg);
  Serial.print("Enviando: "); Serial.println(msg);
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
