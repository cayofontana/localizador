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
                        construir();
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
        if (mensagem.indexOf(",A,") >= 0) {
                hora = getDado(mensagem, ',', 1);
                latitude = getDado(mensagem, ',', 3);
                orientacaoLatitude = getDado(mensagem, ',', 4);
                longitude = getDado(mensagem, ',', 5);
                orientacaoLongitude = getDado(mensagem, ',', 6);
                velocidade = getDado(mensagem, ',', 7);
                data = getDado(mensagem, ',', 9);
                Serial.println("Hora: " + hora);
                Serial.println("Latitude: " + latitude);
                Serial.println("Orientação Latitude: " + orientacaoLatitude);
                Serial.println("Longitude: " + longitude);
                Serial.println("Orientação Longitude: " + orientacaoLongitude);
                Serial.println("velocidade: " + velocidade);
                Serial.println("Data: " + data);
        }
}

String
Dado::getDado(String mensagem, char separador, int vezesOcorrencia)
{
        int vezOcorrenciaAtual, indice, indiceFinal;
        String mensagemParcial;

        for (indice = vezOcorrenciaAtual = 0; vezOcorrenciaAtual < vezesOcorrencia; ++vezOcorrenciaAtual)
                indice = mensagem.indexOf(separador, indice == 0 ? indice : indice + 1);

        mensagemParcial = mensagem.substring(indice + 1);
        indiceFinal = mensagemParcial.indexOf(separador);

        return (mensagemParcial.substring(0, indiceFinal));
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
