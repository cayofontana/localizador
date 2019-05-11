#ifndef LED_H
#define LED_H

#include "Semaforo.h"
#include <Arduino.h>

class Led
{
public:
        static void notificar(Semaforo);
        static void inicializar(void);
        static void limpar(void);
        static void ligar(uint8_t);
        static void desligar(uint8_t);

private:
        Led();
};

#endif
