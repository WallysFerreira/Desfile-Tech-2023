#include <Wire.h>

#define PIR_1_LIN_1 0x01
#define PIR_1_LIN_2 0x02
#define PIR_1_LIN_3 0x03
#define PIR_1_LIN_4 0x04

#define PIN_ECHO1 1
#define PIN_TRIGGER1 2
#define PIN_ECHO2 3 
#define PIN_TRIGGER2 4

#define ESQUERDA 0xF3
#define CIMA 0xF2
#define DIREITA 0xF1

byte PIR1[] = {PIR_1_LIN_1, PIR_1_LIN_2, PIR_1_LIN_3, PIR_1_LIN_4};
byte PIR2[] = {PIR_1_LIN_1, PIR_1_LIN_2, PIR_1_LIN_3, PIR_1_LIN_4};
byte MOTORES[] = {0x01, 0x02, 0x03, 0x04};
byte LEDS[] = {0xA1, 0xA2, 0xA3, 0xA4};

bool passouPeloFinal = false;
bool passouPelaEntrada = false;

void setup() {
    pinMode(PIN_TRIGGER1, OUTPUT);
    pinMode(PIN_TRIGGER2, OUTPUT);
    pinMode(PIN_ECHO1, INPUT);
    pinMode(PIN_ECHO2, INPUT);

    Serial.begin(9600);
    Wire.begin();
}

void loop() {
    digitalWrite(PIN_TRIGGER1, LOW);
    digitalWrite(PIN_TRIGGER2, LOW);

    // Fazer chamadas na API

    // Checar o sensor ultrassonico do começo
    digitalWrite(PIN_TRIGGER1, HIGH);
    digitalWrite(PIN_TRIGGER2, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_TRIGGER1, LOW);
    digitalWrite(PIN_TRIGGER2, LOW);

    int distancia1 = pulseIn(PIN_ECHO1, HIGH) * 0.034 / 2;
    int distancia2 = pulseIn(PIN_ECHO2, HIGH) * 0.034 / 2;

    if (distancia1 < 20) {
        if (!passouPelaEntrada) {
            Serial.println("Passou pela entrada pela primeira vez");
            mexerMotoresPiramide1(ESQUERDA, DIREITA);
        } else {
            Serial.println("Passou pela entrada pela segunda vez");
            mexerMotoresPiramide1(DIREITA, ESQUERDA);
        }

        passouPelaEntrada = !passouPelaEntrada;
    }

    // Checar o sensor ultrassonico do anguloFinal
    if (distancia2 < 20) {
        if (!passouPeloFinal) {
            Serial.println("Passou pelo final pela primeira vez");
            mexerMotoresPiramide2(ESQUERDA, DIREITA);
        } else {
            Serial.println("Passou pelo final pela segunda vez");
            mexerMotoresPiramide2(DIREITA, ESQUERDA);
        }

        passouPeloFinal = !passouPeloFinal;
    }
}

void vermelhoPiramide1() {
    byte data[] = {0xA5, 0xFF, 0x00, 0x00};
    for (int i = 0; i < sizeof(PIR1) / sizeof(byte); i++) {
        Wire.beginTransmission(PIR1[i]);
        for (int i = 0; i < sizeof(data) / sizeof(byte); i++) {
            Wire.write(data[i]);
        }
        Wire.endTransmission();
    }
}

void mexerMotoresPiramide1(int anguloComeco, int anguloFinal) {
    byte data[] = {0x05, anguloComeco, anguloFinal, 0x02};
    for (int i = 0; i < sizeof(PIR1) / sizeof(byte); i++) {
        Wire.beginTransmission(PIR1[i]);
        for (int i = 0; i < sizeof(data) / sizeof(byte); i++) {
            Wire.write(data[i]);
        }
        Wire.endTransmission();
    }
}

void mexerMotoresPiramide2(int anguloComeco, int anguloFinal) {
    byte data[] = {0x05, anguloComeco, anguloFinal, 0x02};
    for (int i = 0; i < sizeof(PIR2) / sizeof(byte); i++) {
        Wire.beginTransmission(PIR2[i]);
        for (int i = 0; i < sizeof(data) / sizeof(byte); i++) {
            Wire.write(data[i]);
        }
        Wire.endTransmission();
    }
}