#include "ComunicacaoMovel.h"


ComunicacaoMovel::ComunicacaoMovel(const char *gprsAPN, const char *gprsUsuario, const char *gprsSenha, const char *servidor, const char *endereco, uint8_t porta, uint8_t pinoLed, Status *status) {
        this->gprsAPN = gprsAPN;
        this->gprsUsuario = gprsUsuario;
        this->gprsSenha = gprsSenha;
        this->servidor = servidor;
        this->endereco = endereco;
        this->porta = porta;
        this->status = status;
        this->pinoLed = pinoLed;
        pinMode(pinoLed, OUTPUT);
}

ComunicacaoMovel::~ComunicacaoMovel() {
        desconectar();
}

bool
ComunicacaoMovel::conectar(void) {
        Led::ligar(pinoLed);

        int i = 0;
        while (gsm.begin(CODIGO_PIN) != GSM_READY || gprs.attachGPRS(gprsAPN, gprsUsuario, gprsSenha) != GPRS_READY) {
                statusMudou(Semaforo::ALERTA);
                if (++i > maximoTentativaConexoes)
                        return (false);
                delay(2500);
        }
        statusMudou(Semaforo::NORMAL);
        return (true);
}

bool
ComunicacaoMovel::enviar(Dado *dado) {
        if (conectar()) {
                if (clienteGSM.connect(servidor, 8080)) {
                        String strHttpQueryString = dado->toHTTPQueryString();
                        char httpQueryString[sizeof(strHttpQueryString)];
                        strHttpQueryString.toCharArray(httpQueryString, sizeof(strHttpQueryString));
                        clienteGSM.print("GET ");
                        clienteGSM.print(endereco + strHttpQueryString);
                        clienteGSM.println(" HTTP/1.0");
                        clienteGSM.println();
                        Serial.println("Enviado!");
                        statusMudou(Semaforo::NORMAL);
                }
                else {
                        Serial.println("ERRO!");
                        statusMudou(Semaforo::ALERTA);
                }
                // ler();
        }
        desconectar();
}

void
ComunicacaoMovel::desconectar(void) {
        if (!clienteGSM.connected())
                clienteGSM.stop();
        Led::desligar(pinoLed);
}

void
ComunicacaoMovel::ler(void) {
        String respostaHTTP = "";
        bool teste = true;
        
        while (teste) {
                if (clienteGSM.available()) {
                        char caractere = clienteGSM.read();
                        respostaHTTP += caractere;
                        char caractereResposta[respostaHTTP.length() + 1];
                        respostaHTTP.toCharArray(caractereResposta, respostaHTTP.length() + 1);
                        if (strstr(caractereResposta, "200 OK") != NULL) {
                                Serial.println(caractereResposta);
                        }
                }
                teste = false;
        }
}

Status *
ComunicacaoMovel::getStatus(void) {
        return (status);
}

void
ComunicacaoMovel::statusMudou(Semaforo semaforo) {
        status->setSemaforo(semaforo);
        status->notificarGerente(dynamic_cast<IStatusProdutor&>(*this));
}
