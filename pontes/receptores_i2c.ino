#include <Wire.h>
#include "base.hpp"

// Mudar conforme a linha onde o arduino for colocado, de cima para baixo
#define MINHA_LINHA 0x02

// Mudar confome a quantidade de motores na linha
#define MOTOR1 3
#define MOTOR2 6
#define MOTOR3 7
#define MOTOR4 8

#define VERMELHO1 5
#define VERDE1 2
#define AZUL1 3

#define VERMELHO2 9
#define VERDE2 10
#define AZUL2 11

#define VERMELHO3 12
#define VERDE3 13
#define AZUL3 14

#define VERMELHO4 15
#define VERDE4 16
#define AZUL4 17

Servo m1;
Servo m2;
Servo m3;
Servo m4;

void setup() {
    Serial.begin(9600);
    Wire.begin(MINHA_LINHA);
    Wire.onReceive(eventoReceber);
    m1.attach(MOTOR1);
    m2.attach(MOTOR2);
    m3.attach(MOTOR3);
    m4.attach(MOTOR4);
}

byte oqueMudar;
byte parametro1;
byte parametro2;
byte parametro3;

void loop() {
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

    Serial.println(parametro1);
    Serial.println(parametro2);
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
        case 0xA1:
            mudarLuz(VERMELHO1, VERDE1, AZUL1, parametro1, parametro2, parametro3);
            break;
        case 0xA2:
            mudarLuz(VERMELHO2, VERDE2, AZUL2, parametro1, parametro2, parametro3);
            break;
        case 0xA3:
            mudarLuz(VERMELHO3, VERDE3, AZUL3, parametro1, parametro2, parametro3);
            break;
        case 0xA4:
            mudarLuz(VERMELHO4, VERDE4, AZUL4, parametro1, parametro2, parametro3);
            break;
        case 0xA5:
            mudarLuz(VERMELHO1, VERDE1, AZUL1, parametro1, parametro2, parametro3);
            mudarLuz(VERMELHO2, VERDE2, AZUL2, parametro1, parametro2, parametro3);
            mudarLuz(VERMELHO3, VERDE3, AZUL3, parametro1, parametro2, parametro3);
            mudarLuz(VERMELHO4, VERDE4, AZUL4, parametro1, parametro2, parametro3);
            break;
    }
}