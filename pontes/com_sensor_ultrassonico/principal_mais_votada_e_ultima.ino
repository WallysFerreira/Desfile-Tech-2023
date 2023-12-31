#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>

ESP8266WiFiMulti WiFiMulti;

// Credenciais para wifi
struct Credenciais {
  const char* ssid;
  const char* senha;
};

Credenciais networks[] = {
  {"SENAC-Mesh", "09080706"},
  {"Vivo-Internet-E532", "6EFC366C"},
  {"AP1501", "ARBBBE11"},
  {"iPhone de Arnott", "arbbbe11"},
};

#define PIR_1_LIN_1 0x01
#define PIR_1_LIN_2 0x02
#define PIR_1_LIN_3 0x03
#define PIR_1_LIN_4 0x04
#define PIR_2_LIN_1 0x05
#define PIR_2_LIN_2 0x06
#define PIR_2_LIN_3 0x07
#define PIR_2_LIN_4 0x08

#define PIN_ECHO1 D5
#define PIN_TRIGGER1 D6
#define PIN_ECHO2 D7
#define PIN_TRIGGER2 D8

#define ESQUERDA 0xF3
#define CIMA 0xF2
#define DIREITA 0xF1

byte PIR1[] = {PIR_1_LIN_1, PIR_1_LIN_2, PIR_1_LIN_3, PIR_1_LIN_4};
byte PIR2[] = {PIR_2_LIN_1, PIR_2_LIN_2, PIR_2_LIN_3, PIR_2_LIN_4};
byte MOTORES[] = {0x01, 0x02, 0x03, 0x04};
byte LEDS[] = {0xA1, 0xA2, 0xA3, 0xA4};

bool passouPeloFinal = false;
bool passouPelaEntrada = false;

void conectarWifi() {
  for (int i = 0; i < sizeof(networks) / sizeof(networks[0]); i++) {
    WiFiMulti.addAP(networks[i].ssid, networks[i].senha);
    Serial.printf("Tentando conectar a %s...\n", networks[i].ssid);

    // Aguarda a conexão por até 10 segundos
    for (int j = 0; j < 10; j++) {
      if (WiFiMulti.run() == WL_CONNECTED) {
        Serial.printf("Conectado a %s\n", networks[i].ssid);
        return; // Conexão bem-sucedida, saia da função
      }
      delay(1000);
    }
    delay(1000);
    Serial.printf("Falha na conexão a %s\n", networks[i].ssid);
//    WiFiMulti.removeAP(networks[i].ssid); // Remove a rede da lista para tentar a próxima
  }
}

void setup() {
    pinMode(PIN_TRIGGER1, OUTPUT);
    pinMode(PIN_TRIGGER2, OUTPUT);
    pinMode(PIN_ECHO1, INPUT);
    pinMode(PIN_ECHO2, INPUT);

    Serial.begin(9600);
    Wire.begin();
}

String ultimaMaisVotada;
String ultima;
void loop() {
    conectarWifi();
   
    digitalWrite(PIN_TRIGGER1, LOW);
    digitalWrite(PIN_TRIGGER2, LOW);

    // Fazer chamadas na API
    if (WiFiMulti.run() == WL_CONNECTED) {
      WiFiClient client;
      HTTPClient http;

      if (http.begin(client, "http://recnplay2023.pythonanywhere.com/resultados")) {
        Serial.print("[HTTP] Get... \n");
        int httpCode = http.GET();
        if (httpCode > 0) {
          if (httpCode == HTTP_CODE_OK) {
            String payload = http.getString();
            Serial.println(payload);

            const size_t capacity = JSON_OBJECT_SIZE(3);
            StaticJsonDocument<200> doc;

            DeserializationError error = deserializeJson(doc, payload); 

            if (!error) {
              int qntdVermelho = doc["vermelho"];
              int qntdAzul = doc["azul"];
              int qntdVerde = doc["verde"];
              String maisVotada;
              String ultimaVotada = doc["ultimo"];

              Serial.printf("Vermelho: %d\n", qntdVermelho);
              Serial.printf("Verde: %d\n", qntdVerde);
              Serial.printf("Azul: %d\n", qntdAzul);

              if (qntdVermelho >= qntdVerde && qntdVermelho >= qntdAzul) {
                maisVotada = "vermelho";
              }
              else if (qntdVerde >= qntdVermelho && qntdVerde >= qntdAzul) {
                maisVotada = "verde";
              }
              else if (qntdAzul >= qntdVermelho && qntdAzul >= qntdVerde) {
                maisVotada = "azul";
              }

              if (ultimaMaisVotada != maisVotada) {
                ultimaMaisVotada = maisVotada;

                mudarCorPiramide(ultimaMaisVotada, "mais");
              }

              if (ultimaVotada != ultima) {
                ultima = ultimaVotada;

                mudarCorPiramide(ultima, "ultima");
              }
            } else {
              Serial.println("Falha no parse JSON");
            }
          }
        } else {
          Serial.printf("[HTTP] Get... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }
        http.end();
      } else {
        Serial.println("[HTTP] Não conseguiu conectar");
      }

      
    }
    // Pegar distancia dos sensores
      digitalWrite(PIN_TRIGGER1, HIGH);
      delayMicroseconds(10);
      digitalWrite(PIN_TRIGGER1, LOW);

      int duration = pulseIn(PIN_ECHO1, HIGH);
      int distancia1 = duration * 0.034 / 2;
      delay(300);

      digitalWrite(PIN_TRIGGER2, HIGH);
      delayMicroseconds(10);
      digitalWrite(PIN_TRIGGER2, LOW);
      int duration2 = pulseIn(PIN_ECHO2, HIGH);
      int distancia2 = duration2 * 0.034 / 2;
      Serial.print("Distancia sensor 1: ");
      Serial.println(distancia1);
      Serial.print("Distancia sensor 2: ");
      Serial.println(distancia2);
    
      // Checar o sensor ultrassonico do começo
      if (distancia1 < 15) {
        if (!passouPelaEntrada) {
            Serial.println("Passou pela entrada pela primeira vez");
            mexerMotores(ESQUERDA, DIREITA, 1);
        } else {
            Serial.println("Passou pela entrada pela segunda vez");
            mexerMotores(DIREITA, ESQUERDA, 1);
        }

        passouPelaEntrada = !passouPelaEntrada;
      }
    

    // Checar o sensor ultrassonico do final
      if (distancia2 < 20) {
        if (!passouPeloFinal) {
            Serial.println("Passou pelo final pela primeira vez");
            mexerMotores(ESQUERDA, DIREITA, 2);
        } else {
            Serial.println("Passou pelo final pela segunda vez");
            mexerMotores(DIREITA, ESQUERDA, 2);
        }

        passouPeloFinal = !passouPeloFinal;
      }
      delay(200);
}

void mudarCorPiramide(String cor, String qualCor) {
  byte qual;

  if (qualCor == "mais") qual = 0xA5;
  if (qualCor == "ultima") qual = 0xA6;

  if (cor == "vermelho") {
    mudarTodosLeds(qual, 0xFF, 0x00, 0x00);
  } else if (cor == "verde") {
    mudarTodosLeds(qual, 0x00, 0xFF, 0x00);
  } else if (cor == "azul") {
    mudarTodosLeds(qual, 0x00, 0x00, 0xFF);
  }
}

void mudarTodosLeds(byte maisVotadaOuUltima, byte qntdVermelho, byte qntdVerde, byte qntdAzul) { 
    byte data[] = {maisVotadaOuUltima, qntdVermelho, qntdVerde, qntdAzul};

    for (int i = 0; i < sizeof(PIR1) / sizeof(byte); i++) {
      Wire.beginTransmission(PIR1[i]);
      for (int j = 0; j < sizeof(data) / sizeof(byte); j++) {
        Wire.write(data[j]);
      }
      Wire.endTransmission();
    }
    for (int i = 0; i < sizeof(PIR2) / sizeof(byte); i++) {
      Wire.beginTransmission(PIR2[i]);
      for (int j = 0; j < sizeof(data) / sizeof(byte); j++) {
        Wire.write(data[j]);
      }
      Wire.endTransmission();
    }
}

void mexerMotores(int anguloComeco, int anguloFinal, int qualPiramide) {
  byte data[] = {0x05, anguloComeco, anguloFinal, 0x02};
  
  switch (qualPiramide) {
    case 1:
      for (int i = 0; i < sizeof(PIR1) / sizeof(byte); i++) {
        Wire.beginTransmission(PIR1[i]);
        for (int j = 0; j < sizeof(data) / sizeof(byte); j++) {
            Wire.write(data[j]);
        }
        Wire.endTransmission();
      }
      break;
    case 2:
      for (int i = 0; i < sizeof(PIR2) / sizeof(byte); i++) {
        Wire.beginTransmission(PIR2[i]);
        for (int j = 0; j < sizeof(data) / sizeof(byte); j++) {
            Wire.write(data[j]);
        }
        Wire.endTransmission();
      }
      break;
    }
}