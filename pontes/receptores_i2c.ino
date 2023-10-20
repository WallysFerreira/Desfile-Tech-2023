#include <Wire.h>
#include "base.hpp"

// Mudar conforme a linha onde o arduino for colocado, de cima para baixo
#define MINHA_LINHA 0x06

// Mudar confome a quantidade de motores na linha
#define MOTOR1 3
#define MOTOR2 5
#define MOTOR3 6
#define MOTOR4 9

#define VERMELHO1 2
#define VERDE1 4
#define AZUL1 7

#define VERMELHO2 8
#define VERDE2 12
#define AZUL2 13

#define VERMELHO3 A0
#define VERDE3 A1
#define AZUL3 A2

#define VERMELHO4 A3
#define VERDE4 A4
#define AZUL4 A5

Servo m1;
Servo m2;
Servo m3;
Servo m4;

int pinosVermelhos[4] = {VERMELHO1, VERMELHO2, VERMELHO3, VERMELHO4};
int pinosVerdes[4] = {VERDE1, VERDE2, VERDE3, VERDE4};
int pinosAzuis[4] = {AZUL1, AZUL2, AZUL3, AZUL4};

void setup() {
    Serial.begin(9600);
    Wire.begin(MINHA_LINHA);
    Wire.onReceive(eventoReceber);
    colocarTodosLedsHigh();
    m1.attach(MOTOR1);
    m2.attach(MOTOR2);
    m3.attach(MOTOR3);
    m4.attach(MOTOR4);
}

byte oqueMudar;
byte parametro1;
byte parametro2;
byte parametro3;

String maisVotada = "";
String ultima = "";

void loop() {
    // Alternar entre mais votada e ultima usando fade
    acenderLed(maisVotada);

    acenderLed(ultima);

    Serial.print("maisVotada: ");
    Serial.println(maisVotada);
    Serial.print("ultima: ");
    Serial.println(ultima);
}

void eventoReceber(int _) {
    while (Wire.available()) {
        oqueMudar = Wire.read();
        parametro1 = Wire.read();
        parametro2 = Wire.read();
        parametro3 = Wire.read();
    }
    Serial.println("recebeu: ");
    Serial.println(oqueMudar, HEX);
    Serial.println(parametro1, HEX);
    Serial.println(parametro2, HEX);
    Serial.println(parametro3, HEX);

    if (parametro1 == 0xF1) parametro1 = 0;
    if (parametro1 == 0xF2) parametro1 = 90;
    if (parametro1 == 0xF3) parametro1 = 180;
    if (parametro2 == 0xF1) parametro2 = 0;
    if (parametro2 == 0xF2) parametro2 = 90;
    if (parametro2 == 0xF3) parametro2 = 180;

    switch (oqueMudar) {
        case 0x01:
            mexerMotor(m1, parametro1, parametro2, parametro3);
            break;
        case 0x02:
            mexerMotor(m2, parametro1, parametro2, parametro3);
            break;
        case 0x03:
            mexerMotor(m3, parametro1, parametro2, parametro3);
            break;
        case 0x04:
            mexerMotor(m4, parametro1, parametro2, parametro3);
            break;
        case 0x05:
            mexerMotor(m1, parametro1, parametro2, parametro3);
            mexerMotor(m2, parametro1, parametro2, parametro3);
            mexerMotor(m3, parametro1, parametro2, parametro3);
            mexerMotor(m4, parametro1, parametro2, parametro3);
            break;
            /*
        case 0xA1:
            mudarLuz(parametro1, parametro2, parametro3);
            break;
        case 0xA2:
            mudarLuz(parametro1, parametro2, parametro3); 
            break;
        case 0xA3:
            mudarLuz(parametro1, parametro2, parametro3);
            break;
        case 0xA4:
            mudarLuz(parametro1, parametro2, parametro3);
            break;
            */
        case 0xA5:
            if (parametro1 == 0xFF) maisVotada = "vermelho";
            if (parametro2 == 0xFF) maisVotada = "verde";
            if (parametro3 == 0xFF) maisVotada = "azul";
            break;
        case 0xA6:
            if (parametro1 == 0xFF) ultima = "vermelho";
            if (parametro2 == 0xFF) ultima = "verde";
            if (parametro3 == 0xFF) ultima = "azul";
            break;/*
        case 0xA7:
            if (parametro1 == 0xFF) analogWrite(10, 0);
            if (parametro1 == 0x00) analogWrite(10, 255);*/
    }
}

void colocarTodosLedsHigh() {
    analogWrite(VERMELHO1, 255);
    analogWrite(VERMELHO2, 255);
    analogWrite(VERMELHO3, 255);
    analogWrite(VERMELHO4, 255);
    analogWrite(VERDE1, 255);
    analogWrite(VERDE2, 255);
    analogWrite(VERDE3, 255);
    analogWrite(VERDE4, 255);
    analogWrite(AZUL1, 255);
    analogWrite(AZUL2, 255);
    analogWrite(AZUL3, 255);
    analogWrite(AZUL4, 255);
}

void acenderLed(String cor) {    
    if (cor == "vermelho") {
      Serial.println("ligando leds vermelhos");
        for (int j = 0; j < sizeof(pinosVermelhos) / sizeof(int); j++) {
            analogWrite(pinosVermelhos[j], 0);
        }

        delay(400);

        for (int j = 0; j < sizeof(pinosVermelhos) / sizeof(int); j++) {
            analogWrite(pinosVermelhos[j], 255);
        }

        delay(400);
    } else if (cor == "verde") {
        for (int j = 0; j < sizeof(pinosVerdes) / sizeof(int); j++) {
            analogWrite(pinosVerdes[j], 0);
        }

        delay(400);

        for (int j = 0; j < sizeof(pinosVerdes) / sizeof(int); j++) {
            analogWrite(pinosVerdes[j], 255);
        }

        delay(400);
    } else if (cor == "azul") {

        for (int j = 0; j < sizeof(pinosAzuis) / sizeof(int); j++) {
            analogWrite(pinosAzuis[j], 0);
        }

        delay(400);

        for (int j = 0; j < sizeof(pinosAzuis) / sizeof(int); j++) {
            analogWrite(pinosAzuis[j], 255);
        }

        delay(400);
    }
}
