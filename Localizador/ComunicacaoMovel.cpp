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

        while (!conectado)
                if ((gsm.begin(CODIGO_PIN) == GSM_READY) && (gprs.attachGPRS(gprsAPN, gprsUsuario, gprsSenha) == GPRS_READY)) {
                        conectado = true;
                        Led::notificar(Semaforo::NORMAL);
                }
                else
                        Led::notificar(Semaforo::ATENCAO);
}


bool
ComunicacaoMovel::enviar(Dado dado) {
        conectar();
        
        if (clienteGSM.connect(servidor, porta)) {
                clienteGSM.print("GET ");
                clienteGSM.print(endereco + (String) "?" + dado.toHTTPQueryString());
                clienteGSM.println(" HTTP/1.1");
                clienteGSM.print("Host: ");
                clienteGSM.println(servidor);
                clienteGSM.println("Connection: close");
                clienteGSM.println();
                
                Led::notificar(Semaforo::NORMAL);
        }
        else {
                Led::notificar(Semaforo::ALERTA);
        }

        desconectar();
}

void
ComunicacaoMovel::desconectar(void) {
        if (!clienteGSM.available() && !clienteGSM.connected()) {
                clienteGSM.stop();
        }
}

void
ComunicacaoMovel::ler(void) {
        if (clienteGSM.available()) {
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
