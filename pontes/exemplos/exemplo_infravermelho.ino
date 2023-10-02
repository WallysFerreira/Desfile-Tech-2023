#include <IRremote.hpp>

#define PINO_RECEPTOR 7
#define PINO_EMISSOR 8

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(PINO_RECEPTOR);  
  IrSender.begin(PINO_EMISSOR);
}

void loop() {
  // Formato: Address, Command, Repeats
  IrSender.sendNEC(0x1, 0x1, 1);
  
  if (IrReceiver.decode()) {  
    IrReceiver.printIRResultShort(&Serial);

    IrReceiver.resume();
  }

  delay(1000);
}
