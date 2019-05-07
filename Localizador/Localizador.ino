#include "Dado.h"
#include "Persistencia.h"
#include "ComunicacaoMovel.h"
#include "Semaforo.h"
#include "Status.h"
#include "Util.h"

GerenteStatus *gerenteStatus = GerenteStatus::obterInstancia(3);
Persistencia persistencia("dado_gps.txt", 4, new Status(gerenteStatus));
Dado dado(new Status(gerenteStatus));
ComunicacaoMovel comunicacaoMovel("zap.vivo.com.br", "vivo", "vivo", "201.140.235.74", "cadastrodadogps.jsp", 8080, new Status(gerenteStatus));

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
                if (!dado.leituraCompletou()) {
                        //dado.construir();
                        //persistencia.salvar(dado.toHTTPQueryString());
                        //persistencia.listar();
                        //comunicacaoMovel.enviar(dado);
                }
        }
}
