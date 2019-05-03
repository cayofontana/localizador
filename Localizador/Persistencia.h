#ifndef PERSISTENCIA_H
#define PERSISTENCIA_H

#include <SPI.h>
#include <SD.h>
#include "Status.h"

class Persistencia : public IStatusProdutor
{
public:
        Persistencia(String nomeArquivo, uint8_t pino, Status *status);
        ~Persistencia();
        
        void inicializar(void);
        bool salvar(String strHTTPQueryString);
        void listar(void);
        virtual Status *getStatus(void) override;
        virtual void statusMudou(Semaforo) override;

private:
      File arquivo;
      Status *status;
      String nomeArquivo;
      uint8_t pino;
};

#endif
