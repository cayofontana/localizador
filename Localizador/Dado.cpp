#include "Dado.h"

Dado::Dado(Status *status) : status(status) {
        this->status = status;
        testeAnterior = 0;
        proximaLeitura = false;
        leituraParada = false;
        mensagem = "";
}

Dado::~Dado() {
        delete status;
}

void
Dado::inicializar(void) {
        SerialGPS.begin(9600);
        while (!Serial)
                continue;
}

bool
Dado::deveLer(void) {
        if (millis() - testeAnterior >= INTERVALO * 1000UL) {
                testeAnterior = millis();
                if (leituraParada)
                        leituraParada = false; 
        }

        return (!leituraParada);
}

void
Dado::obterMensagemGPS() {
        char caractere;
        
        if ((SerialGPS.available() > 0) && !proximaLeitura && !leituraParada) {
                if ((caractere = SerialGPS.read()) == '\n')
                        proximaLeitura = true;
                else
                        mensagem += caractere;
        }
}

bool
Dado::leituraCompletou(void) {
        if (proximaLeitura) {
                if (mensagem.startsWith("$GPRMC")) {
                        Serial.println(mensagem);
                        leituraParada = true;
                }
                proximaLeitura = false;
                mensagem = "";
        }

        return (!proximaLeitura);
}

void
Dado::construir(void) {
 
}

String
Dado::toHTTPQueryString() {
        return ("lat=" + String(latitude, 6) + "&lon=" + String(longitude, 6) + "&alt=" + altitude + "&vel=" + velocidade + "&dth=" + data + "" + hora);
}

void
Dado::preencher(void) {

}

Status *
Dado::getStatus(void) {
        return (status);
}

void
Dado::statusMudou(Semaforo semaforo) {
        status->setSemaforo(semaforo);
        status->notificarGerente(dynamic_cast<IStatusProdutor&>(*this));
}
