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

void
ComunicacaoMovel::inicializar(void) {
        conectar();
}

bool
ComunicacaoMovel::conectar(void) {
        desconectar();
        
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
        int i, maximo;

        for (i = 0, maximo = 10; !clienteGSM.connected() && !clienteGSM.connect(servidor, 8080) && i < maximo; ++i) {
                statusMudou(Semaforo::ALERTA);
                delay(5000);
        }

        if (i == maximo) {
                statusMudou(Semaforo::ALERTA);
                conectar();
                return (false);
        }
        else {
                Led::ligar(pinoLed);                        
                String strHttpQueryString = dado->toHTTPQueryString();                
                clienteGSM.print("GET ");
                clienteGSM.print(endereco + strHttpQueryString);
                clienteGSM.println(" HTTP/1.0");
                clienteGSM.println();
                statusMudou(Semaforo::NORMAL);
                Led::desligar(pinoLed);
                return (true);
        }
}

void
ComunicacaoMovel::desconectar(void) {
        if (!clienteGSM.connected())
                clienteGSM.stop();
        gsm.shutdown();
        delay(5000);
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
