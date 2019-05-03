#ifndef GERENTESTATUS_H
#define GERENTESTATUS_H

#include <stdlib.h>
#include "IStatusProdutor.h"
#include "IStatusConsumidor.h"
#include "Semaforo.h"
#include "Led.h"

class GerenteStatus : public IStatusConsumidor
{
public:
        GerenteStatus(int);
        ~GerenteStatus();

        static GerenteStatus *obterInstancia(int);
        void atualizarStatusGlobal(IStatusProdutor &produtor);
        void adicionar(IStatusProdutor &produtor) override;
        void notificar(Semaforo semaforo) override;

private:
        static GerenteStatus *instancia;
        IStatusProdutor **produtores;
        int quantidade_produtores;
        Semaforo semaforoStatusGlobal;
};

#endif
