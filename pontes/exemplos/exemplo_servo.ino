#include <Servo.h>

#define SERVO 5

Servo s;

void setup() {
    s.attach(SERVO);
    Serial.begin(9600);
    s.write(90);
}

void loop() {
    s.write(180);
    delay(200);
    s.write(90);
    delay(200);
}