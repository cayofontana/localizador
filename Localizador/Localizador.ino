#include "Dado.h"
#include "Persistencia.h"
#include "ComunicacaoMovel.h"
#include "Semaforo.h"
#include "Status.h"
#include "Util.h"

GerenteStatus *gerenteStatus = GerenteStatus::obterInstancia();
Persistencia persistencia("dado_gps.txt", 7, *gerenteStatus);
Dado dado(4, *gerenteStatus);
ComunicacaoMovel comunicacaoMovel("zap.vivo.com.br", "vivo", "vivo", "201.140.232.75", "/cadastrodadogps.jsp?", 8080, 5, *gerenteStatus);

void setup() {
//        Serial.begin(9600);
        // USADO PARA USB-CDC APENAS
//        while (!Serial)
//                continue;
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
