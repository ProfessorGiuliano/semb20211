#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "WebSocketsClient.h"
#include "StompClient.h"

/**
* Definições
**/

#define nome "nome do wifi"
#define senha "senha do wifi"

#define ipServidor "ip do servidor"

/**
* Configurações
**/

const char* wlan_ssid             = nome;
const char* wlan_password         = senha;

bool useWSS                       = true;
const char* ws_host               = ipServidor;
const int ws_port                 = 8080;
const char* ws_baseurl            = "/ws/"; // don't forget leading and trailing "/" !!!

bool sample = false;
int blink = 0;
bool blinkOn = false;
long lastBlinked;

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
  
    stomper.onConnect(subscribe);
    stomper.onError(error);
    stomper.begin();
}

void subscribe(Stomp::StompCommand cmd) {
    Serial.println("Connected to STOMP broker");
    stomper.subscribe("/channel/output-1", Stomp::CLIENT, handleSampleMessage);
    stomper.subscribe("/channel/output-2", Stomp::CLIENT, handleBlinkMessage);
}

void error(const Stomp::StompCommand cmd) {
    Serial.println("ERROR: " + cmd.body);
}
Stomp::Stomp_Ack_t handleSampleMessage(const Stomp::StompCommand cmd) {
    Serial.println("Got a message!");
    Serial.println(cmd.body);

    sample = true;
    return Stomp::CONTINUE;
}

Stomp::Stomp_Ack_t handleBlinkMessage(const Stomp::StompCommand cmd) {
    Serial.println("Got a message!");
    Serial.println(cmd.body);

    return Stomp::CONTINUE;
}

void takeSample() {
    static int counter = 0;
    if (sample) {
        stomper.sendMessage("/server/input", "Mensagem " + String(counter++));
        sample = false;
    }
}

void loop() {
    webSocket.loop();
    takeSample();
}
