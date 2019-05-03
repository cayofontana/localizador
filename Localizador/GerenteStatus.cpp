#include "GerenteStatus.h"
#include "Status.h"

GerenteStatus* GerenteStatus::instancia = 0;

GerenteStatus::GerenteStatus(int quantidade_produtores) {
        this->quantidade_produtores = 0;
        produtores = new IStatusProdutor *[quantidade_produtores];
        semaforoStatusGlobal = Semaforo::ATENCAO;
        notificar(semaforoStatusGlobal);
}

GerenteStatus::~GerenteStatus() {
        
}

GerenteStatus *
GerenteStatus::obterInstancia(int quantidade_produtores)
{
        if (instancia == 0)
                instancia = new GerenteStatus(quantidade_produtores);
        return (instancia);
}

void
GerenteStatus::atualizarStatusGlobal(IStatusProdutor &produtor) {
        
        Semaforo semaforoAtual = semaforoStatusGlobal;
        Status *status = dynamic_cast<IStatusProdutor&>(produtor).getStatus();

        if (status->getSemaforo() != semaforoStatusGlobal)
                semaforoStatusGlobal = status->getSemaforo();

        for (int i = 0; i < quantidade_produtores; ++i)
                if (&produtores[i] != &produtor && produtores[i]->getStatus()->getSemaforo() > semaforoStatusGlobal)
                        semaforoStatusGlobal = produtores[i]->getStatus()->getSemaforo();
    
        if (semaforoAtual != semaforoStatusGlobal)
                notificar(semaforoStatusGlobal);
}

void
GerenteStatus::adicionar(IStatusProdutor &produtor) {
          produtores[quantidade_produtores++] = &produtor;
}

void
GerenteStatus::notificar(Semaforo semaforo) {
        Led::notificar(semaforo);
}
