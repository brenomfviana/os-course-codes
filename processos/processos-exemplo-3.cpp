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
            exit(1);
        case 0:             // Retorno do fork para o Processo Filho
            for (int i = 0; i < 10; i++) {
                printf("Sou o Processo Filho ID: %d\n", getpid());
                sleep(5);
            }
            break;
        default:
            for (int i = 0; i < 10; i++) {
                printf("Sou o Processo Pai ID: %d\n", getpid());
                sleep(5);
            }
            break;
    }

    return 0;
}
