#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    pid_t id_processo;
    int status_retorno;
    int count = 0;

    id_processo = fork();

    if (id_processo < 0) {
        exit(errno);
    }

    if (id_processo != 0) { // Processo Pai
        wait(&status_retorno); // Espera bloqueante pela morte do Processo Filho
        if (WIFEXITED(status_retorno)) {
            printf("O Processo Filho finalizou normalmente: %d\n", WEXITSTATUS(status_retorno));
        } else if (WIFSIGNALED(status_retorno)) {
            printf("O Processo Filho foi cancelado por um sinal: %d\n", WTERMSIG(status_retorno));
        }
    }

    if (id_processo == 0) { // Processo Filho
        while (count++ < 10) {
            printf("Processo Filho: %d\n", getpid());
            sleep(2);
        }
        exit(0);
    }

    return 0;
}
