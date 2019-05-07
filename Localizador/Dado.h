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
        String toHTTPQueryString(void);
        virtual Status *getStatus(void) override;
        virtual void statusMudou(Semaforo) override;
        
private:
        String latitude;
        String orientacaoLatitude;
        String longitude;
        String orientacaoLongitude;
        String velocidade;
        String data;
        String hora;
        Status *status;

        unsigned long testeAnterior;
        bool proximaLeitura;
        bool leituraParada;
        String mensagem;

        void construir(void);
        String getDado(String mensagem, char separador, int indice);
};

#endif
