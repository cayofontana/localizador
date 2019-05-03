#ifndef ISTATUSPRODUTOR_H
#define ISTATUSPRODUTOR_H

class Status;
enum class Semaforo;

class IStatusProdutor
{
public:
        virtual Status *getStatus(void) = 0;
        virtual void statusMudou(Semaforo) = 0;
};

#endif;
