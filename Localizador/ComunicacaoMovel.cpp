#include "ComunicacaoMovel.h"


ComunicacaoMovel::ComunicacaoMovel(const char* gprsAPN, const char* gprsUsuario, const char* gprsSenha, const char* servidor, const char* endereco, uint8_t porta, uint8_t pinoLed, GerenteStatus& gerenteStatus) : gprsAPN(gprsAPN), gprsUsuario(gprsUsuario), gprsSenha(gprsSenha), servidor(servidor), endereco(endereco), porta(porta), pinoLed(pinoLed), gerenteStatus(gerenteStatus) {
        status = new Status(&gerenteStatus);
        pinMode(pinoLed, OUTPUT);
        gerenteStatus.adicionar(this);
}

ComunicacaoMovel::~ComunicacaoMovel() {
        desconectar();
}

bool
ComunicacaoMovel::enviar(Dado* dado) {
        if (conectar() && clienteGSM.connect(servidor, 8080)) {
                Led::ligar(pinoLed);                        
                String strHttpQueryString = dado->toHTTPQueryString();                
                clienteGSM.print("GET ");
                clienteGSM.print(endereco + strHttpQueryString);
                clienteGSM.println(" HTTP/1.0");
                clienteGSM.println();
                delay(2000);
                clienteGSM.flush();
                clienteGSM.stop();
                statusMudou(Semaforo::NORMAL);
                Led::desligar(pinoLed);
                return (true);
        }
        statusMudou(Semaforo::ALERTA);
        return (false);
}

bool
ComunicacaoMovel::conectar(void) {
        desconectar();
        
        if (gsm.begin(CODIGO_PIN) != GSM_READY || gprs.attachGPRS(gprsAPN, gprsUsuario, gprsSenha) != GPRS_READY) {
                desconectar();
                statusMudou(Semaforo::ALERTA);
                return (false);
        }
        statusMudou(Semaforo::NORMAL);
        return (true);
}

void
ComunicacaoMovel::desconectar(void) {
        if (!clienteGSM.connected())
                clienteGSM.stop();
        gsm.shutdown();
        delay(5000);
}

Status*
ComunicacaoMovel::getStatus(void) {
        return (status);
}

void
ComunicacaoMovel::statusMudou(Semaforo semaforo) {
        status->setSemaforo(semaforo);
        status->notificarGerente(this);
}
