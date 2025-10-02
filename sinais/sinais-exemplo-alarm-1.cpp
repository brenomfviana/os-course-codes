#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

// Função signal handler responsável por tratar o sinal
void detectarAlarme(int sig) {
    printf("O alarme expirou!\n");
    exit(1);
}

int main(int argc, char *argv[]) {
    // Instala o tratamento do alarme
    signal(SIGALRM, detectarAlarme);

    unsigned int tempoRestanteAlarmeAnterior;
    tempoRestanteAlarmeAnterior = alarm(5);
    printf("Tempo restante do alarme anterior: %d\n", tempoRestanteAlarmeAnterior);
    sleep(2);

    // Ao chamar alarm() antes do alarme anterior expirar,
    // faz com que o alarme anterior seja perdido
    tempoRestanteAlarmeAnterior = alarm(5);
    printf("Tempo restante do alarme anterior: %d\n", tempoRestanteAlarmeAnterior);
    sleep(1);

    tempoRestanteAlarmeAnterior = alarm(5);
    printf("Tempo restante do alarme anterior: %d\n", tempoRestanteAlarmeAnterior);
    
    // Loop sem atividade
    while(true) {
        sleep(1);
        printf("Esperar ser finalizado\n");
    }

    return 0;
}
