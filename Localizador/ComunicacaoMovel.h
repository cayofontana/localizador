#ifndef COMUNICACAOMOVEL_H
#define COMUNICACAOMOVEL_H

#include <MKRGSM.h>
#include "Dado.h"
#include "Status.h"

#define CODIGO_PIN ""

const int maximoTentativaConexoes = 30;

class ComunicacaoMovel : public IStatusProdutor
{
public:
        ComunicacaoMovel(const char *, const char *, const char *, const char *, const char *, uint8_t, uint8_t, Status *);
        ~ComunicacaoMovel();

        void inicializar(void);
        bool enviar(Dado *);
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
        uint8_t pinoLed;

        bool conectar(void);
        void enviar(const char *);
        void desconectar(void);
};

#endif
