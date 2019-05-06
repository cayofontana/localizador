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
        void obterMensagemGPS(void);
        bool leituraCompletou(void);
        void construir(void);
        String toHTTPQueryString(void);
        virtual Status *getStatus(void) override;
        virtual void statusMudou(Semaforo) override;
        
private:
        double latitude;
        char orientacaoLatitude;
        double longitude;
        char orientacaoLongitude;
        double velocidade;
        uint32_t data;
        uint32_t hora;
        Status *status;

        unsigned long testeAnterior;
        bool proximaLeitura;
        bool leituraParada;
        String mensagem;
        
        String getDado(String mensagem, char separador, int indice);
};

#endif
