#ifndef GERENTESTATUS_H
#define GERENTESTATUS_H

#include <stdlib.h>
#include <list>
#include "IStatusProdutor.h"
#include "IStatusConsumidor.h"
#include "Semaforo.h"
#include "Led.h"

class GerenteStatus : public IStatusConsumidor
{
public:
        ~GerenteStatus();
        
        static GerenteStatus* obterInstancia();
        void atualizarStatusGlobal(IStatusProdutor*);
        void adicionar(IStatusProdutor*) override;
        void notificar(Semaforo) override;

private:
        static GerenteStatus* instancia;
        std::list<IStatusProdutor*> produtores;
        Semaforo semaforoStatusGlobal;

        GerenteStatus();
};

#endif
