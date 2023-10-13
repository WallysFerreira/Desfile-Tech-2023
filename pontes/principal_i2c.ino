#include <Wire.h>
#include <Ultrasonic.h>

#define PIR_1_LIN_1 0x01
#define PIR_1_LIN_2 0x02
#define PIR_1_LIN_3 0x03
#define PIR_1_LIN_4 0x04

#define PIN_ECHO1 
#define PIN_TRIGGER1
#define PIN_ECHO2
#define PIN_TRIGGER2

#define ESQUERDA 0xF3
#define CIMA 0xF2
#define DIREITA 0xF1

byte PIR1[] = {PIR_1_LIN_1, PIR_1_LIN_2, PIR_1_LIN_3, PIR_1_LIN_4};

HC_SR04 sensorEntrada(PIN_TRIGGER1, PIN_ECHO1);
HC_SR04 sensorFinal(PIN_TRIGGER2, PIN_ECHO2); 

bool passouPeloFinal = false;
bool passouPelaEntrada = false;

void setup() {
    Serial.begin(9600);
    Wire.begin();
}

void loop() {
    // Fazer chamadas na API

    // Checar o sensor ultrassonico do começo
    if (sensorEntrada.distance() < 20) {
        if (!passouPelaEntrada) {
            Serial.println("Passou pelo entrada pela primeira vez");
            mexerMotoresPiramide1(ESQUERDA, PIRAMIDE);
        } else {
            Serial.println("Passou pelo entrada pela segunda vez");
            mexerMotoresPiramide1(DIREITA, ESQUERDA);
        }

        passouPelaEntrada = !passouPelaEntrada;
    }

    // Checar o sensor ultrassonico do anguloFinal
    if (sensorFinal.distance() < 20) {
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
    for (int i = 0; i < PIR1.length(); i++) {
        Wire.beginTransmission(PIR1[i]);
        Wire.write([0xA5, 0xFF, 0x00, 0x00]);
        Wire.endTransmission();
    }
}

void mexerMotoresPiramide1(int anguloComeco, int anguloFinal) {
    for (int i = 0; i < PIR1.length(); i++) {
        Wire.beginTransmission(PIR1[i]);
        Wire.write([0x05, anguloComeco, anguloFinal, 0x02]);
        Wire.endTransmission();
    }
}

void mexerMotoresPiramide2(int anguloComeco, int anguloFinal) {
    for (int i = 0; i < PIR2.length(); i++) {
        Wire.beginTransmission(PIR2[i]);
        Wire.write([0x05, anguloComeco, anguloFinal, 0x02]);
        Wire.endTransmission();
    }
}