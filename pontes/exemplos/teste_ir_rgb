#include <IRremote.h>

#define RECV_PIN 3 // Pino onde o receptor infravermelho está conectado

IRrecv irrecv(RECV_PIN);
decode_results results;

#define LED_VERMELHO 12 // Pino onde o LED vermelho está conectado
#define LED_AZUL 11     // Pino onde o LED azul está conectado
#define LED_VERDE 10    // Pino onde o LED verde está conectado

#define BT_VERMELHO 0xFF7A85
#define BT_AZUL 0xFF30CF
#define BT_VERDE 0xFF18E7
#define BT_PISCAR 0xFF52AD // Adicione um novo código para o botão "Piscar"

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn(); // Inicializa o receptor IR
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_AZUL, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  apagaLeds(); // Certifique-se de que os LEDs estão apagados no início
}

bool piscando = false;

void loop() {
    // Caso contrário, aguarde um sinal IR e acenda o LED correspondente
    if (irrecv.decode(&results)) {
      // Se um código infravermelho for recebido, imprima-o no monitor serial
      Serial.println(results.value, HEX);

      // Verifique o código recebido e acenda o LED na cor correspondente
      switch (results.value) {
        case BT_VERMELHO:
          acendeVermelho();
          piscando = false;
          break;
        case BT_AZUL:
          acendeAzul();
          piscando = false;
          break;
        case BT_VERDE:
          acendeVerde();
          piscando = false;
          break;
        case BT_PISCAR:
          piscando = true;
      }

      irrecv.resume(); // Reinicializa o receptor IR
    }

  if (piscando) {
    piscarLeds();
  }
}

void apagaLeds() {
  digitalWrite(LED_VERMELHO, LOW);
  digitalWrite(LED_AZUL, LOW);
  digitalWrite(LED_VERDE, LOW);
}

void acendeVermelho() {
  apagaLeds();
  digitalWrite(LED_VERMELHO, HIGH);
}

void acendeAzul() {
  apagaLeds();
  digitalWrite(LED_AZUL, HIGH);
}

void acendeVerde() {
  apagaLeds();
  digitalWrite(LED_VERDE, HIGH);
}

void piscarLeds() {
  for (int i = 0; i < 3; i++) { // Piscar 3 vezes
    apagaLeds();
    delay(50); // Leds apagados por 500 ms
    acendeVermelho();
    delay(50); // Vermelho aceso por 500 ms
    apagaLeds();
    delay(50); // Leds apagados por 500 ms
    acendeAzul();
    delay(50); // Azul aceso por 500 ms
    apagaLeds();
    delay(50); // Leds apagados por 500 ms
    acendeVerde();
    delay(50); // Verde aceso por 500 ms
  }
}
