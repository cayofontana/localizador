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
}

ComunicacaoMovel::~ComunicacaoMovel() {
        desconectar();
}

bool
ComunicacaoMovel::conectar(void) {
        while (gsm.begin(CODIGO_PIN) != GSM_READY) {
                statusMudou(Semaforo::ALERTA);
                delay(2500);
        }
        if (gprs.attachGPRS(gprsAPN, gprsUsuario, gprsSenha) != GPRS_READY) {
                statusMudou(Semaforo::ALERTA);
                return (false);
        }
        statusMudou(Semaforo::NORMAL);
        return (true);
}

bool
ComunicacaoMovel::enviar(Dado *dado) {
        if (conectar()) {
                Led::ligar(pinoLed);
                int respostaConexao = clienteGSM.connect(servidor, 8080);                
                String strHttpQueryString = dado->toHTTPQueryString();
                char httpQueryString[sizeof(strHttpQueryString)];
                strHttpQueryString.toCharArray(httpQueryString, sizeof(strHttpQueryString));
                
                if (respostaConexao > 0) {
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
                Led::desligar(pinoLed);
                ler();
        }
        desconectar();
}

void
ComunicacaoMovel::desconectar(void) {
        if (!clienteGSM.connected())
                clienteGSM.stop();
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
