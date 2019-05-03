#include "Dado.h"
#include "Persistencia.h"
#include "Semaforo.h"
#include "Status.h"
#include "Util.h"

GerenteStatus *gerenteStatus = GerenteStatus::obterInstancia(2);
Persistencia persistencia("dado_gps.txt", 4, new Status(gerenteStatus));
Dado dado(2, 3, new Status(gerenteStatus));

void setup() {
        Serial.begin(9600);
        gerenteStatus->adicionar(persistencia);
        gerenteStatus->adicionar(dado);
        while (!Serial);
        persistencia.inicializar();
}

void loop() {
        dado.construir();

        if (dado.estahDisponivel()) {
                persistencia.salvar(dado.toHTTPQueryString());
                persistencia.listar();
                delay(29000);
                Util::limparBufferSerial();
        }
}
