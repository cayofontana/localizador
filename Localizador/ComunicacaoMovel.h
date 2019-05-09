#ifndef COMUNICACAOMOVEL_H
#define COMUNICACAOMOVEL_H

#include <MKRGSM.h>
#include "Dado.h"
#include "Status.h"

#define CODIGO_PIN ""

class ComunicacaoMovel : public IStatusProdutor
{
public:
        ComunicacaoMovel(const char *GPRS_APN, const char *GPRS_USUARIO, const char *GPRS_SENHA, const char *servidor, const char *endereco, uint8_t porta, Status *status);
        ~ComunicacaoMovel();
        
        bool enviar(Dado *dado);
        virtual Status *getStatus(void) override;
        virtual void statusMudou(Semaforo) override;
        
private:
        GSMClient clienteGSM;
        GPRS gprs;
        GSM gsm;
        const char *gprsAPN;
        const char *gprsUsuario;
        const char *gprsSenha;
        const char *servidor;
        const char *endereco;
        uint8_t porta;
        Status *status;

        void conectar(void);
        void desconectar(void);
        void ler(void);
};

#endif
