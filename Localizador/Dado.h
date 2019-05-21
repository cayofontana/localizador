#ifndef DADO_H
#define DADO_H

#include <Arduino.h>
#include "Status.h"

#define SerialGPS Serial1
#define INTERVALO 30

class Dado : public IStatusProdutor
{
public:
        Dado(uint8_t, Status *);
        ~Dado();

        void inicializar(void);
        bool deveLer(void);
        void obterMensagemGPS(void);
        bool leituraCompletou(void);
        String toHTTPQueryString(void);
        bool atualizou(void);
        void reiniciar(void);
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
        uint8_t pinoLed;

        unsigned long testeAnterior;
        bool proximaLeitura;
        bool leituraParada;
        String mensagem;

        bool atualizado;

        bool construir(void);
        String getDado(String, char, int);
};

#endif
