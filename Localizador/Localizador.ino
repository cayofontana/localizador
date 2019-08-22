#include "Dado.h"
#include "Persistencia.h"
#include "ComunicacaoMovel.h"
#include "Semaforo.h"
#include "Status.h"
#include "Util.h"

GerenteStatus *gerenteStatus = GerenteStatus::obterInstancia(3);
Persistencia persistencia("dado_gps.txt", 7, new Status(gerenteStatus));
Dado dado(4, new Status(gerenteStatus));
ComunicacaoMovel comunicacaoMovel("zap.vivo.com.br", "vivo", "vivo", "201.140.232.75", "/cadastrodadogps.jsp?", 8080, 5, new Status(gerenteStatus));

void setup() {
        Serial.begin(9600);
        // USADO PARA USB-CDC APENAS
//        while (!Serial)
//                continue;
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
                        // USADO APENAS PARA CHECAGEM NO SERIAL MONITOR DO ARDUINO IDE
                        // persistencia.listar();
                        comunicacaoMovel.enviar(&dado);
                        dado.reiniciar();
                }
        }
}
