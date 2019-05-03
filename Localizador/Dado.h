#ifndef DADO_H
#define DADO_H

#include <SoftwareSerial.h>
#include "TinyGPS++.h"
#include "Status.h"

class Dado : public IStatusProdutor
{
public:
        Dado(uint8_t pinoRX, uint8_t pinoTX, Status *status);
        ~Dado();

        void construir(void);        
        String toHTTPQueryString(void);
        bool estahDisponivel(void);
        SoftwareSerial *getSoftwareSerial(void);
        virtual Status *getStatus(void) override;
        virtual void statusMudou(Semaforo) override;
        
private:
        SoftwareSerial *softwareSerial;
        TinyGPSPlus gps;
        double latitude;
        double longitude;
        double altitude;
        double velocidade;
        uint32_t data;
        uint32_t hora;
        Status *status;
        
        bool disponivel;

        bool atualizou(void);
        void preencher(void);
};

#endif
