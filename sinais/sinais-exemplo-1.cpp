#include <csignal>
#include <cstdio>
#include <unistd.h>

// Função signal handler responsável por tratar o sinal
void signal_handler(int sig) {
    printf("Não adianta usar o sinal: %d\n", sig);
    printf("O processo apenas finaliza com um kill -9 %d\n", getpid());
}

int main(int argc, char *argv[]) {
    // Instala a função para tratar o sinal de interrupção de terminal
    signal(SIGINT, signal_handler);
    while(1) {
        printf("Processo: %d vai dormir por 1 segundo.\n", getpid());
        sleep(1);
    }
    return 0;
}
