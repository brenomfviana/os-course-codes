#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

// Função signal handler responsável por tratar o sinal
void detectar_alarme(int sig) {
    printf("O alarme expirou!\n");
    exit(0);
}

int main(int argc, char *argv[]) {
    // Instala o tratamento do alarme
    signal(SIGALRM, detectar_alarme);

    unsigned int tempo_restante;
    tempo_restante = alarm(5);
    printf("Tempo restante do alarme anterior: %d\n", tempo_restante);
    sleep(2);

    // Ao chamar alarm() antes do alarme anterior expirar,
    // faz com que o alarme anterior seja perdido
    tempo_restante = alarm(5);
    printf("Tempo restante do alarme anterior: %d\n", tempo_restante);
    sleep(1);

    tempo_restante = alarm(5);
    printf("Tempo restante do alarme anterior: %d\n", tempo_restante);
    
    // Loop sem atividade
    while(true) {
        sleep(1);
        printf("Esperar ser finalizado\n");
    }

    return 0;
}
