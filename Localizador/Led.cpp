#include "Led.h"

void
Led::inicializar(void) {
        pinMode((int) Semaforo::NORMAL, OUTPUT);
        pinMode((int) Semaforo::ATENCAO, OUTPUT);
        pinMode((int) Semaforo::ALERTA, OUTPUT);
}

void
Led::notificar(Semaforo semaforo) {
        limpar();
        switch (semaforo)
        {
                case Semaforo::NORMAL:
                        digitalWrite((int) semaforo, HIGH);
                        break;
                case Semaforo::ATENCAO:
                        //digitalWrite((int) semaforo, HIGH);
                        digitalWrite((int) Semaforo::NORMAL, HIGH);
                        digitalWrite((int) Semaforo::ALERTA, HIGH);
                        break;
                case Semaforo::ALERTA:
                        digitalWrite((int) semaforo, HIGH);
                        break;
        }  
}

void 
Led::ligar(uint8_t pino) {
        digitalWrite(pino, HIGH);
}

void
Led::desligar(uint8_t pino) {
        digitalWrite(pino, LOW);
}

void
Led::limpar(void) {
        digitalWrite((int) Semaforo::NORMAL, LOW);
        digitalWrite((int) Semaforo::ATENCAO, LOW);
        digitalWrite((int) Semaforo::ALERTA, LOW);
}
