#include <StringSplitter.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <stdio.h>
#include <stdlib.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Ultrasonic.h>
#include <Servo.h>

/* Pinagem
   ---------------------
   | Função  | Pino |
   ---------------------
   Sonar:
   |   Trig  |   D3    |
   |   Echo  |   D4    |
   Giroscópio:
   |   SCL   |   D6    |
   |   SDA   |   D5    |
   Servo:
   |   Com   |   D0    |
   Ponte H:
   | MotorA1 |   D0    | Amarelo
   | MotorA2 |   D5    | Verde
   | MotorB1 |   D6    | Azul
   | MotorB2 |   D7    | Roxo
*/
ESP8266WebServer server(80);
Ultrasonic ultrasonic(D3, D4);
Servo s;

String wifiName = "Tales07";
String wifiPass = "S3m_S3nh@";
int medidas[180];

Adafruit_MPU6050 mpu;

String req;


void setup() {
  Serial.begin(115200);
  while (!Serial) continue;

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

  server.on("/", handleBody);

  server.begin();

  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

  s.attach(D0);
  s.write(0);

  pinMode(D8, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  digitalWrite(D8, LOW);
  digitalWrite(D5, LOW);
  digitalWrite(D6, LOW);
  digitalWrite(D7, LOW);


  digitalWrite(D4, LOW);
}

void loop() {
  server.handleClient();

  
}

void handleBody() { //Handler for the body path

  if (server.hasArg("plain") == false) { //Check if body received

    server.send(200, "text/plain", "Aguardando Comandos");
    return;

  }
  req = server.arg("plain");
  
  String message = "Body received:\n";
  message += req;
  message += "\n";
  
  String comando[5];
  Serial.print("Msg: "); Serial.println(req);
  StringSplitter *splitter = new StringSplitter(req, '/', 5);
  int itemCount = splitter->getItemCount();

  for (int i = 0; i < itemCount; i++) {
    comando[i] = splitter->getItemAtIndex(i);
  }

  Serial.print("comando[0]: "); Serial.println(comando[0]);
  Serial.print("comando[1]: "); Serial.println(comando[1]);
  Serial.print("comando[2]: "); Serial.println(comando[2]);
  Serial.print("comando[3]: "); Serial.println(comando[3]);


  if (comando[0] == "movimento") {
    int temp = comando[2].toInt();
    movimento(comando[1], temp);
  } else if (comando[0] == "leitura") {
    if(comando[1]=="sensores"){
      
    }else if(comando[1]=="giro"){
      
    }else if(comando[1]=="ace"){
      
    }else if(comando[1]=="sonar"){
      
    }
  }

  server.send(200, "text/plain", "ExecutandoComando");
  Serial.println(message);
}



void hold(const unsigned int &ms) {
  // Non blocking hold
  unsigned long m = millis();
  while (millis() - m < ms) {
    yield();
  }
}

void leituraSonar() {
  long microsec = ultrasonic.timing();

  for (int i = 0; i < 180; i++) {
    s.write(i);
    medidas[i] = (int)ultrasonic.convert(microsec, Ultrasonic::CM);
    hold(100);
  }
  req = "/sonar/";
  for (int j = 0; j < 180; j++) {
    req += medidas[j];
    req += "/";
  }
  enviar(req);
}



void enviar(String msg) {
  server.send(200, "text/plain", msg);
}

void giroAce(){
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  req = "giroAce/";
  req += g.gyro.x;
  req += "/";
  req += g.gyro.y;
  req += "/";
  req += g.gyro.z;
  req +=  "/";
  req += a.acceleration.x;
  req +=  "/";
  req += a.acceleration.y;
  req += "/";
  req += a.acceleration.z;
  enviar(req);
}

void movimento(String comando, int temp) {
  enviar("Em movimento");
  if (comando == "f") {
    frenteOn();
    hold(temp);
    direcaoOFF();
  } else if (comando == "r") {
    reOn();
    hold(temp);
    direcaoOFF();
  } else if (comando == "d") {
    direitaOn();
    hold(temp);
    direcaoOFF();
  } else if (comando == "e") {
    esquerdaOn();
    hold(temp);
    direcaoOFF();
  }
}

void frenteOn() {
  digitalWrite(D5, HIGH);
  digitalWrite(D6, LOW);
  digitalWrite(D7, HIGH);
  digitalWrite(D8, LOW);
}
void reOn() {
  digitalWrite(D5, LOW);
  digitalWrite(D6, HIGH);
  digitalWrite(D7, LOW);
  digitalWrite(D8, HIGH);
}
void direitaOn() {
  digitalWrite(D5, HIGH);
  digitalWrite(D6, LOW);
  digitalWrite(D7, LOW);
  digitalWrite(D8, HIGH);
}
void esquerdaOn() {
  digitalWrite(D5, LOW);
  digitalWrite(D6, HIGH);
  digitalWrite(D6, HIGH);
  digitalWrite(D8, LOW);
}
void direcaoOFF() {
  digitalWrite(D5, LOW);
  digitalWrite(D6, LOW);
  digitalWrite(D7, LOW);
  digitalWrite(D8, LOW);
}
