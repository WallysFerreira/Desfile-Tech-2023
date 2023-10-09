#include <Wire.h>

#define PIR_1_LIN_1 0x01
#define PIR_1_LIN_2 0x02
#define PIR_1_LIN_3 0x03
#define PIR_1_LIN_4 0x04

byte PIR1[] = {PIR_1_LIN_1, PIR_1_LIN_2, PIR_1_LIN_3, PIR_1_LIN_4};

void setup() {
    Serial.begin(9600);
    Wire.begin();
}

void loop() {
}

void vermelhoPiramide1() {
    for (int i = 0; i < PIR1.length(); i++) {
        Wire.beginTransmission(PIR1[i]);
        Wire.write([0xA1, 0xFF, 0x00, 0x00]);
        Wire.write([0xA2, 0xFF, 0x00, 0x00]);
        Wire.write([0xA3, 0xFF, 0x00, 0x00]);
        Wire.write([0xA4, 0xFF, 0x00, 0x00]);
        Wire.endTransmission();
    }
}

void motorEsquerdaParaDireitaPiramide1() {
    for (int i = 0; i < PIR1.length(); i++) {
        Wire.beginTransmission(PIR1[i]);
        Wire.write([0x01, 0xF1, 0xF3, 0x02]);
        Wire.endTransmission();
    }
}