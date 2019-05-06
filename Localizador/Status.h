#ifndef STATUS_H
#define STATUS_H

#include <Arduino.h>
#include "Semaforo.h"
#include "GerenteStatus.h"

class Status
{
public:
        Status(GerenteStatus *gerenteStatus);
        ~Status();

        void limpar(void);
        Semaforo getSemaforo(void);
        void setSemaforo(Semaforo semaforo);
        void notificarGerente(IStatusProdutor &);

private:
        GerenteStatus *gerenteStatus;
        Semaforo semaforo;

};

#endif
