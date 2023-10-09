#include <Wire.h>

#define PIR_1_LIN_1 0x01
#define PIR_1_LIN_2 0x02
#define PIR_1_LIN_3 0x03
#define PIR_1_LIN_4 0x04

byte PIR1 = [PIR_1_LIN_1, PIR_1_LIN_2, PIR_1_LIN_3, PIR_1_LIN_4];

void setup() {
    Serial.begin(9600);
    Wire.begin();
}

void loop() {
}

void vermelhoPiramide1() {
    for (int i = 0; i < PIR1.length(); i++) {
        Wire.beginTransmission(PIR1[i]);
        Wire.write([0xAA, 0xFF, 0x00, 0x00]);
        Wire.endTransmission();
    }
}

void motorEsquerdaParaDireitaPiramide1() {
    for (int i = 0; i < PIR1.length(); i++) {
        Wire.beginTransmission(PIR1[i]);
        Wire.write([0xAF, 0x00, 0xFF, 0x02]);
        Wire.endTransmission();
    }
}