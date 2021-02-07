#include "Persistencia.h"

Persistencia::Persistencia(String nomeArquivo, uint8_t pino, GerenteStatus& gerenteStatus) : nomeArquivo(nomeArquivo), pino(pino), gerenteStatus(gerenteStatus) {
        status = new Status(&gerenteStatus);
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
Persistencia::salvar(Dado* dado) {
        arquivo = SD.open(nomeArquivo, FILE_WRITE);
        
        if (arquivo) {
                arquivo.println(dado->toHTTPQueryString());
                arquivo.close();
                statusMudou(Semaforo::NORMAL);
                return (true);
        }
        else {
                statusMudou(Semaforo::ATENCAO);
                return (false);
        }
}


// MÉTODO USADO PARA TESTE (SERIAL MONITOR)
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

Status*
Persistencia::getStatus(void) {
        return (status);
}

void
Persistencia::statusMudou(Semaforo semaforo) {
        status->setSemaforo(semaforo);
        status->notificarGerente(this);
}
