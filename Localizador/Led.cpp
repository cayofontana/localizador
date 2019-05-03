#include "Led.h"

void
Led::notificar(Semaforo semaforo) {
        limpar();
        switch (semaforo)
        {
                case Semaforo::NORMAL:
                        digitalWrite((int) semaforo, HIGH);
                        break;
                case Semaforo::ATENCAO:
                        digitalWrite((int) semaforo, HIGH);
                        break;
                case Semaforo::ALERTA:
                        digitalWrite((int) semaforo, HIGH);
                        break;
        }  
}

void
Led::inicializar(void) {
        pinMode((int) Semaforo::NORMAL, OUTPUT);
        pinMode((int) Semaforo::ATENCAO, OUTPUT);
        pinMode((int) Semaforo::ALERTA, OUTPUT);
}

void
Led::limpar(void) {
        digitalWrite((int) Semaforo::NORMAL, LOW);
        digitalWrite((int) Semaforo::ATENCAO, LOW);
        digitalWrite((int) Semaforo::ALERTA, LOW);
}
