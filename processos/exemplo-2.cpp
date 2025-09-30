#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    pid_t id_processo;

    printf("Iniciando programa\n");

    id_processo = fork();

    switch (id_processo) {
        case -1:            // Erro na geração do Processo Filho
            exit(-1);
        case 0:             // Processo Filho
            printf("Sou o Processo Filho ID: %d, Pai ID: %d\n", getpid(), getppid());
            break;
        default:            // Processo Pai
            printf("Sou o Processo Pai ID: %d, Avô ID: %d, Processo Filho ID: %d\n", getpid(), getppid(), id_processo);
            break;
    }

    return 0;
}
