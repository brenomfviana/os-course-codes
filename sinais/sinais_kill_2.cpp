#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

// Função signal handler responsável por tratar o sinal
void signal_handler(int sig) {
    printf("Não adianta usar o sinal: %d\n", sig);
    printf("Apenas termino com um kill -9 %d\n", getpid());
    // Instala a função default para SIGINT, nesse caso um exit
    signal (SIGINT, SIG_DFL);
}

int main(int argc, char *argv[]) {
    // Identificador do processo
    pid_t id_processo;
    printf("Iniciando o programa\n");

    // Instala a função para tratar o sinal do usuário
    signal(SIGUSR1, signal_handler);

    // Cria o processo
    id_processo = fork();
    
    switch(id_processo) {
        case -1:        // Erro na abertura do processo filho
            exit(1);
        case 0:         // Retorno de fork para processo filho
            while(1){
                printf("Sou o Processo Filho ID: %d, Pai ID: %d\n", getpid(), getppid());
                sleep(1);
            }           
            break;
        default:        // Processo pai
            int cont = 0;
            while(1) {
                printf("Sou o Processo Pai com ID: %d, Avô ID: %d, Filho ID: %d\n", getpid(), getppid(), id_processo);
                sleep(1);
                if (cont++ == 4) {
                    // Finaliza o processo filho
                    kill(id_processo, SIGUSR1);
                }
            }
            break;
    }
    return 0;
}
