#ifndef PERSISTENCIA_H
#define PERSISTENCIA_H

#include <SPI.h>
#include <SD.h>
#include "Status.h"
#include "Dado.h"

class Persistencia : public IStatusProdutor
{
public:
        Persistencia(String, uint8_t, GerenteStatus&);
        ~Persistencia();
        
        void inicializar(void);
        bool salvar(Dado*);
        void listar(void);
        virtual Status* getStatus(void) override;
        virtual void statusMudou(Semaforo) override;

private:
      File arquivo;
      Status* status;
      GerenteStatus& gerenteStatus;
      String nomeArquivo;
      uint8_t pino;
};

#endif
