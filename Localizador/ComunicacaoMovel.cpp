#include "ComunicacaoMovel.h"


ComunicacaoMovel::ComunicacaoMovel(const char *gprsAPN, const char *gprsUsuario, const char *gprsSenha, const char *servidor, const char *endereco, uint8_t porta, Status *status) {
        this->gprsAPN = gprsAPN;
        this->gprsUsuario = gprsUsuario;
        this->gprsSenha = gprsSenha;
        this->servidor = servidor;
        this->endereco = endereco;
        this->porta = porta;
        this->status = status;
}

ComunicacaoMovel::~ComunicacaoMovel() {
        desconectar();
}

void
ComunicacaoMovel::conectar(void) {
        bool conectado = false;

        while (!conectado) {
                if ((gsm.begin(CODIGO_PIN) == GSM_READY) && (gprs.attachGPRS(gprsAPN, gprsUsuario, gprsSenha) == GPRS_READY)) {
                        conectado = true;
                        //Led::notificar(Semaforo::NORMAL);
                        Serial.println("Conectou!");
                }
                else {
                        //Led::notificar(Semaforo::ATENCAO);
                        Serial.println("Não conectou.");
                }
        }
}


bool
ComunicacaoMovel::enviar(Dado *dado) {
        Serial.print("Conectando a rede GSM...");
                while (gsm.begin(CODIGO_PIN) != GSM_READY) {
                Serial.println("Erro!");
                delay(2500);
        }
        Serial.println("GSM Ok!");
        
        Serial.println("Conectando a rede de telefonia...");
        if (gprs.attachGPRS(gprsAPN, gprsUsuario, gprsSenha) != GPRS_READY) {
                Serial.println("Erro");
        }
        else {
                Serial.println("Ok!");
                Serial.print("Connecting and sending GET request to example.org...");
                
                int respostaConexao = clienteGSM.connect(servidor, 8080);
                
                String strHttpQueryString = dado->toHTTPQueryString();
                char httpQueryString[sizeof(strHttpQueryString)];
                strHttpQueryString.toCharArray(httpQueryString, sizeof(strHttpQueryString));
                
                if (respostaConexao) {
                        clienteGSM.print("GET ");
                        clienteGSM.print(endereco + strHttpQueryString);
                        clienteGSM.println(" HTTP/1.0");
                        clienteGSM.println();
                        Serial.println("Enviado!");
                }
                else {
                        Serial.println("ERRO!");
                }
                Serial.print("Recebendo resposta...");
                String respostaHTTP = "";
                bool teste = true;
                while (teste) {
                        if (clienteGSM.available()) {
                                char c = clienteGSM.read();
                                respostaHTTP += c;
                                char responsechar[respostaHTTP.length() + 1];
                                respostaHTTP.toCharArray(responsechar, respostaHTTP.length() + 1);
                                if (strstr(responsechar, "200 OK") != NULL) {
                                        Serial.println("ok");
                                        Serial.println("TEST COMPLETE!");
                                        teste = false;
                                }
                        }
                        if (!clienteGSM.connected()) {
                                Serial.println();
                                Serial.println("disconnecting.");
                                clienteGSM.stop();
                                teste = false;
                        }
                }
        }
//        String strHttpQueryString = dado.toHTTPQueryString();
//        char httpQueryString[sizeof(strHttpQueryString)];
//        strHttpQueryString.toCharArray(httpQueryString, sizeof(strHttpQueryString));
//        conectar();
//        
//        if (clienteGSM.connect(servidor, porta)) {
//                clienteGSM.print("GET ");
//                clienteGSM.print(endereco + strHttpQueryString);
//                clienteGSM.println(" HTTP/1.0");
//                clienteGSM.println();
//                
//                //Led::notificar(Semaforo::NORMAL);
//                Serial.println("Enviou.");
//        }
//        else {
//                //Led::notificar(Semaforo::ALERTA);
//                Serial.println("Não enviou.");
//        }
//
//        ler();
//
//        desconectar();
}

void
ComunicacaoMovel::desconectar(void) {
        if (!clienteGSM.available() && !clienteGSM.connected()) {
                clienteGSM.stop();
                Serial.println("Desconectou!");
        }
}

void
ComunicacaoMovel::ler(void) {
        while (clienteGSM.available()) {
                char caractere = clienteGSM.read();
                Serial.print(caractere);
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
