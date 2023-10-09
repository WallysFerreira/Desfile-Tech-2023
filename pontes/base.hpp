#include <Servo.h>

#define CIMA 90
#define ESQUERDA 180
#define DIREITA 0

#define DIVIDENDO_VELOCIDADE 150

// Função para controlar motor
void mexerMotor(Servo motor, int posInicial, int posFinal, int velocidade) {
    if (posInicial >  posFinal) {
        for (int i = posInicial; i >= posFinal; i -= velocidade) {
            motor.write(i);
            delay(DIVIDENDO_VELOCIDADE / velocidade);
        }
    } else {
        for (int i = posInicial; i <= posFinal; i += velocidade) {
            motor.write(i);
            delay(DIVIDENDO_VELOCIDADE / velocidade);
        }
    }
}

// Função para controlar luzes
void mudarLuz(int pinoVermelho, int pinoVerde, int pinoAzul, int intensidadeVermelho, int intensidadeVerde, int intensidadeAzul) {
}