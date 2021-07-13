#include <StringSplitter.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include<stdio.h>
#include<stdlib.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Ultrasonic.h> 
/* Pinagem
 * ---------------------    
 * | HC-SC04 | NodeMCU |   
 * ---------------------   
 * |   Vcc   |   5V    |     
 * |   Trig  |   D7    | 
 * |   Echo  |   D8    |   
 * |   Gnd   |   GND   |   
 */
Ultrasonic ultrasonic(D7, D8);

String wifiName = "Tales07";
String wifiPass = "S3m_S3nh@";

Adafruit_MPU6050 mpu;

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

  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
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
    

    if(comando[1]=="comando"){
        sensors_event_t a, g, temp;
        mpu.getEvent(&a, &g, &temp);
        req = "A.x: ";
        req+= a.acceleration.x;
        req+=", y: ";
        req+=a.acceleration.y;
        req+=", A.z: ";
        req+=a.acceleration.y;
        enviar(req);
        hold(100 );
        req="R.x: ";
        req+=g.gyro.x;
        req+=" R.y: ";
        req+=g.gyro.x;
        req+=" R.z: ";
        req+=g.gyro.x;
        enviar(req);
        req = "Distancia: ";
        req+= ultrasonic.distanceRead();
        enviar(req);
        hold(100);
        
    }else if(comando[0] == "REDE"){
      enviar("oi");
    }
    
    req = "";
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
  udp.beginPacket(udp.remoteIP(), 5000);
  udp.println(cstr);
  udp.endPacket();
  Serial.print("Enviando: "); Serial.println(sMsgTemp);
}
