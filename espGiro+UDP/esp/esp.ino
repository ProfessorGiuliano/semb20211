#include <StringSplitter.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include<stdio.h>
#include<stdlib.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

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
  Serial.println("MPU6050 Found!");
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
    case MPU6050_RANGE_2_G:
      Serial.println("+-2G");
      break;
    case MPU6050_RANGE_4_G:
      Serial.println("+-4G");
      break;
    case MPU6050_RANGE_8_G:
      Serial.println("+-8G");
      break;
    case MPU6050_RANGE_16_G:
      Serial.println("+-16G");
      break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
    case MPU6050_RANGE_250_DEG:
      Serial.println("+- 250 deg/s");
      break;
    case MPU6050_RANGE_500_DEG:
      Serial.println("+- 500 deg/s");
      break;
    case MPU6050_RANGE_1000_DEG:
      Serial.println("+- 1000 deg/s");
      break;
    case MPU6050_RANGE_2000_DEG:
      Serial.println("+- 2000 deg/s");
      break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
    case MPU6050_BAND_260_HZ:
      Serial.println("260 Hz");
      break;
    case MPU6050_BAND_184_HZ:
      Serial.println("184 Hz");
      break;
    case MPU6050_BAND_94_HZ:
      Serial.println("94 Hz");
      break;
    case MPU6050_BAND_44_HZ:
      Serial.println("44 Hz");
      break;
    case MPU6050_BAND_21_HZ:
      Serial.println("21 Hz");
      break;
    case MPU6050_BAND_10_HZ:
      Serial.println("10 Hz");
      break;
    case MPU6050_BAND_5_HZ:
      Serial.println("5 Hz");
      break;
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
        req+=" R.x: ";
        req+=g.gyro.x;
        req+=" R.y: ";
        req+=g.gyro.x;
        req+=" R.z: ";
        req+=g.gyro.x;
        enviar(req);
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
  udp.beginPacket(udp.remoteIP(), 1194);
  udp.println(cstr);
  udp.endPacket();
  Serial.print("Enviando: "); Serial.println(sMsgTemp);
}
