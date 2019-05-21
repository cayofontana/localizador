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
        ~GerenteStatus();
        
        static GerenteStatus *obterInstancia(int);
        void atualizarStatusGlobal(IStatusProdutor &);
        void adicionar(IStatusProdutor &) override;
        void notificar(Semaforo) override;

private:
        static GerenteStatus *instancia;
        IStatusProdutor **produtores;
        int quantidade_produtores;
        Semaforo semaforoStatusGlobal;

        GerenteStatus(int);
};

#endif
