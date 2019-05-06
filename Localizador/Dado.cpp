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
        if (proximaLeitura)   {
                if (mensagem.startsWith("$GPRMC")) {
                        Serial.println(mensagem);
                        leituraParada = true;
                }
                proximaLeitura = false;
                mensagem = "";
        }

        return (!proximaLeitura);
}

String
Dado::toHTTPQueryString() {
        return ("lat=" + (String) latitude + "&lon=" + (String) longitude + "&vel=" + (String) velocidade + "&dth=" + (String) data + (String) hora);
}

void
Dado::construir(void) {
        if (getDado(mensagem, ',', 2) == "A") {
                hora = getDado(mensagem, ',', 1).toInt();
                latitude = getDado(mensagem, ',', 3).toDouble();
                orientacaoLatitude = getDado(mensagem, ',', 4).charAt(0);
                longitude = getDado(mensagem, ',', 5).toDouble();
                orientacaoLongitude = getDado(mensagem, ',', 6).charAt(0);
                velocidade = getDado(mensagem, ',', 7).toDouble();
                data = getDado(mensagem, ',', 9).toInt();
                Serial.println("Hora: " + hora);
        }
}

String
Dado::getDado(String mensagem, char separador, int indice)
{
        int achou = 0;
        int strIndex[] = { 0, -1 };
        int indiceMaximo = mensagem.length() - 1;
        
        for (int i = 0; i <= indiceMaximo && achou <= indice; i++) {
                if (mensagem.charAt(i) == separador || i == indiceMaximo) {
                        achou++;
                        strIndex[0] = strIndex[1] + 1;
                        strIndex[1] = (i == indiceMaximo) ? i + 1 : i;
                }
        }
        
        return (achou > indice ? mensagem.substring(strIndex[0], strIndex[1]) : "");
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
