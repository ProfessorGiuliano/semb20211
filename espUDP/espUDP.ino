#include <StringSplitter.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include<stdio.h>
#include<stdlib.h>

String wifiName = "Tales07";
String wifiPass = "S3m_S3nh@";

WiFiUDP udp;
String req;

unsigned int localPort = 8888;
char packetBuffer[UDP_TX_PACKET_MAX_SIZE + 1];
char cstr[50];

char _buffer[64];

void setup() {
  Serial.begin(115200);
  while (!Serial) continue;

  pinMode(D1, OUTPUT);
  pinMode(D4, OUTPUT);
  digitalWrite(D1, LOW);
  digitalWrite(D4, HIGH);

  Serial.println();

  int erro = 0;

  Serial.println("Conectando ao Wifi!");
  WiFi.mode(WIFI_STA);
  WiFi.begin(wifiName, wifiPass);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    hold(200);
  }
  Serial.println("Conectado!");
  hold(500);
  
  udp.begin(localPort);
  digitalWrite(D4, LOW);
}

void loop() {
  listen();
}

void listen() {
  if (udp.parsePacket() > 0) {
    req = "";
    while (udp.available() > 0) {
      char z = udp.read();
      req += z;
    }
    String comando[5];

    StringSplitter *splitter = new StringSplitter(req, '/', 5);  // new StringSplitter(string_to_split, delimiter, limit)
    int itemCount = splitter->getItemCount();

    for (int i = 0; i < itemCount; i++) {
      comando[i] = splitter->getItemAtIndex(i);
    }

    Serial.println("Comando recebido: " + req);
    req = "";

    enviar("oi");

    hold(100);
  }
}

void hold(const unsigned int &ms) {
  // Non blocking hold
  unsigned long m = millis();
  while (millis() - m < ms) {
    yield();
  }
}

void enviar(String msg) {
  String sMsgTemp = "PLACA/Carro/";
  sMsgTemp += msg;
  sMsgTemp.toCharArray(cstr, 50);
  udp.beginPacket(udp.remoteIP(), 1194);
  udp.println(cstr);
  udp.endPacket();
  Serial.print("Enviando: "); Serial.println(sMsgTemp);
}
