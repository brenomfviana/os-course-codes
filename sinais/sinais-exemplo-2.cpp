#include <csignal>
#include <cstdio>
#include <unistd.h>

// Função signal handler responsável por tratar o sinal
void funcaoSignalHandler(int sig) {
    printf("Não adianta usar o sinal: %d\n", sig);
    printf("Apenas termino com um kill -9 %d\n", getpid());
    // Instala a função default para SIGINT, nesse caso um exit
    signal (SIGINT, SIG_DFL);
}

int main(int argc, char *argv[]) {
    // Instala a função para tratar o sinal de interrupção de terminal
    signal(SIGINT, funcaoSignalHandler);
    while(1) {
        printf("Processo: %d vai dormir por 1 segundo.\n", getpid());
        sleep(1);
    }
    return 0;
}
