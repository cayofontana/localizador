#ifndef DADO_H
#define DADO_H

#include <Arduino.h>
#include "Status.h"

#define SerialGPS Serial1
#define INTERVALO 2

class Dado : public IStatusProdutor
{
public:
        Dado(Status *status);
        ~Dado();

        void inicializar(void);
        bool deveLer(void);
        void construir(void);
        void obterMensagemGPS(void);
        bool leituraCompletou(void);
        String toHTTPQueryString(void);
        virtual Status *getStatus(void) override;
        virtual void statusMudou(Semaforo) override;
        
private:
        double latitude;
        double longitude;
        double altitude;
        double velocidade;
        uint32_t data;
        uint32_t hora;
        Status *status;

        unsigned long testeAnterior;
        bool proximaLeitura;
        bool leituraParada;
        String mensagem;

        void preencher(void);
};

#endif
