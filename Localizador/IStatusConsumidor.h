#ifndef ISTATUSCONSUMIDOR_H
#define ISTATUSCONSUMIDOR_H

class IStatusConsumidor
{
public:
        virtual void adicionar(IStatusProdutor&) = 0;
        virtual void notificar(Semaforo) = 0;
};

#endif
