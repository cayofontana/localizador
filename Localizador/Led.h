#ifndef LED_H
#define LED_H

#include "Semaforo.h"
#include <Arduino.h>

class Led
{
public:
        static void notificar(Semaforo semaforo);
        static void inicializar(void);
        static void limpar(void);
};

#endif
