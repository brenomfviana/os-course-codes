#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

int main(int argc, char *argv[]) {
    // Identificador do processo
    pid_t idProcesso;
    printf("Iniciando o programa\n");

    // Cria o processo
    idProcesso = fork();

    switch(idProcesso) {
        case -1:        // Erro na abertura do processo filho
            exit(1);
        case 0:         // Retorno de fork para processo filho
            while(1) {
                printf("Sou o Processo Filho ID: %d, Pai ID: %d\n", getpid(), getppid());
                sleep(1);
            }
            break;
        default:        // Processo pai
            int cont = 0;
            while(1) {
                printf("Sou o Processo Pai com ID: %d, Avô ID: %d, Filho ID: %d\n", getpid(), getppid(), idProcesso);
                sleep(1);
                if (cont++ == 4) {
                    // Finaliza o processo filho
                    kill(idProcesso, SIGKILL);
                }
            }
            break;
    }
    return 0;
}
