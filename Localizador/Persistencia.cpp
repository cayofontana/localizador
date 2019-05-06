#include "Persistencia.h"

Persistencia::Persistencia(String nomeArquivo, uint8_t pino, Status *status) : status(status) {
        this->nomeArquivo = nomeArquivo;
        this->pino = pino;
        this->status = status;
}

Persistencia::~Persistencia() {
        delete status;
}

void
Persistencia::inicializar(void) {
        while (!SD.begin(pino))
                continue;
        SD.remove(nomeArquivo);
}

bool
Persistencia::salvar(String strHTTPQueryString) {
        arquivo = SD.open(nomeArquivo, FILE_WRITE);
        
        if (arquivo) {
                arquivo.println(strHTTPQueryString);
                arquivo.close();
                statusMudou(Semaforo::NORMAL);
                return (true);
        }
        else {
                statusMudou(Semaforo::ATENCAO);
                return (false);
        }
}


// MÉTODO USADO PARA TESte (SERIAL MONITOR)
void 
Persistencia::listar(void) {
        arquivo = SD.open(nomeArquivo);
        
        if (arquivo) {
                Serial.println("Conteúdo do arquivo:");                        
                while (arquivo.available())
                        Serial.write(arquivo.read());
                arquivo.close();
        }
}

Status *
Persistencia::getStatus(void) {
        return (status);
}

void
Persistencia::statusMudou(Semaforo semaforo) {
        status->setSemaforo(semaforo);
        status->notificarGerente(dynamic_cast<IStatusProdutor&>(*this));
}
