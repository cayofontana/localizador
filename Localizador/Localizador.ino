#include "Dado.h"
#include "Persistencia.h"
#include "ComunicacaoMovel.h"
#include "Semaforo.h"
#include "Status.h"
#include "Util.h"

GerenteStatus *gerenteStatus = GerenteStatus::obterInstancia(3);
Persistencia persistencia("dado_gps.txt", 4, new Status(gerenteStatus));
Dado dado(7, new Status(gerenteStatus));
ComunicacaoMovel comunicacaoMovel("zap.vivo.com.br", "vivo", "vivo", "201.140.235.229", "/cadastrodadogps.jsp?", 8080, 5, new Status(gerenteStatus));

void setup() {
        Serial.begin(9600);
        while (!Serial)
                continue;
        gerenteStatus->adicionar(persistencia);
        gerenteStatus->adicionar(dado);
        gerenteStatus->adicionar(comunicacaoMovel);
        dado.inicializar();
        persistencia.inicializar();
}

void loop() {
        if (dado.deveLer()) {
                dado.obterMensagemGPS();
                if (dado.leituraCompletou() && dado.atualizou()) {
                        persistencia.salvar(&dado);
                        persistencia.listar();
                        comunicacaoMovel.enviar(&dado);
                        dado.reiniciar();
                }
        }
}
