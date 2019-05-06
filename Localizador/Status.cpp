#include "Status.h"

Status::Status(GerenteStatus *gerenteStatus) {
        this->gerenteStatus = gerenteStatus;
        semaforo = Semaforo::NORMAL;
        Led::inicializar();
        Led::limpar();
}

Status::~Status() {
        delete gerenteStatus;
}

Semaforo
Status::getSemaforo(void) {
        return (semaforo);
}

void
Status::setSemaforo(Semaforo semaforo) {
        this->semaforo = semaforo;
}

void
Status::notificarGerente(IStatusProdutor &produtor) {
        gerenteStatus->atualizarStatusGlobal(produtor);
}
