#include "Dado.h"

Dado::Dado(Status *status) : status(status) {
        this->status = status;
        testeAnterior = 0;
        proximaLeitura = false;
        leituraParada = false;
        mensagem = "";
        atualizado = false;
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
                        if (construir())
                                atualizado = true;
                        leituraParada = true;
                }
                proximaLeitura = false;
                mensagem = "";
        }

        return (!proximaLeitura);
}

bool
Dado::atualizou(void) {
        return (atualizado);
}

void
Dado::reiniciar(void) {
        atualizado = false;
}

String
Dado::toHTTPQueryString() {
        return ("dis=A2-F3-00-28-31-E3&dth=" + data + hora + "&lat=" + latitude + "&ola=" + orientacaoLatitude + "&lon=" + longitude + "&olo=" + orientacaoLatitude + "&vel=" + velocidade);
}

bool
Dado::construir(void) {
        if (mensagem.indexOf(",A,") >= 0) {
                hora = getDado(mensagem, ',', 1);
                hora = hora.substring(0, hora.indexOf("."));
                latitude = getDado(mensagem, ',', 3);
                orientacaoLatitude = getDado(mensagem, ',', 4);
                longitude = getDado(mensagem, ',', 5);
                orientacaoLongitude = getDado(mensagem, ',', 6);
                velocidade = getDado(mensagem, ',', 7);
                data = getDado(mensagem, ',', 9);
                data = "20" + data.substring(4, 6) + data.substring(2, 4) + data.substring(0, 2);

                return (true);
        }

        return (false);
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
