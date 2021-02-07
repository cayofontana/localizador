#include "GerenteStatus.h"
#include "Status.h"

GerenteStatus* GerenteStatus::instancia = 0;

GerenteStatus::GerenteStatus() {
        semaforoStatusGlobal = Semaforo::ATENCAO;

        // LEDS SENDO INICIALIZADOS, PALIATIVAMENTE, NO CONSTRUTOR DE GERENTESTATUS.
        // ESTE TRECHO DEVE SER MOVIDO PARA DENTRO DO MÉTODO setup() DO ARQUIVO .ino
        Led::inicializar();
        Led::limpar();
        // FIM DO TRECHO
        
        notificar(semaforoStatusGlobal);
}

GerenteStatus::~GerenteStatus() {
        
}

GerenteStatus*
GerenteStatus::obterInstancia()
{
        if (instancia == 0)
                instancia = new GerenteStatus();
        return (instancia);
}

void
GerenteStatus::atualizarStatusGlobal(IStatusProdutor* produtor) {
        
        Semaforo semaforoAtual = semaforoStatusGlobal;

        if (produtor->getStatus()->getSemaforo() != semaforoStatusGlobal)
                semaforoStatusGlobal = produtor->getStatus()->getSemaforo();

        for (std::list<IStatusProdutor*>::iterator _produtor = produtores.begin(); _produtor != produtores.end(); ++_produtor)
                if (*_produtor != produtor && (*_produtor)->getStatus()->getSemaforo() > semaforoStatusGlobal)
                        semaforoStatusGlobal = (*_produtor)->getStatus()->getSemaforo();
    
        if (semaforoAtual != semaforoStatusGlobal)
                notificar(semaforoStatusGlobal);
}

void
GerenteStatus::adicionar(IStatusProdutor* produtor) {
          produtores.push_back(produtor);
}

void
GerenteStatus::notificar(Semaforo semaforo) {
        Led::notificar(semaforo);
}
