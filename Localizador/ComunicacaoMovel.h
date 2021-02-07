#ifndef COMUNICACAOMOVEL_H
#define COMUNICACAOMOVEL_H

#include <MKRGSM.h>
#include "Dado.h"
#include "Status.h"

#define CODIGO_PIN ""

class ComunicacaoMovel : public IStatusProdutor
{
public:
        ComunicacaoMovel(const char*, const char*, const char*, const char*, const char*, uint8_t, uint8_t, GerenteStatus&);
        ~ComunicacaoMovel();

        bool enviar(Dado*);
        virtual Status* getStatus(void) override;
        virtual void statusMudou(Semaforo) override;
        
private:
        GSMClient clienteGSM;
        GPRS gprs;
        GSM gsm;
        const char* gprsAPN;
        const char* gprsUsuario;
        const char* gprsSenha;
        const char* servidor;
        const char* endereco;
        uint8_t porta;
        Status* status;
        GerenteStatus& gerenteStatus;
        uint8_t pinoLed;

        bool conectar(void);
        void desconectar(void);
};

#endif
