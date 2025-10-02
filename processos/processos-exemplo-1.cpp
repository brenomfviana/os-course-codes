#include <cstdio>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    pid_t id_pai;
    pid_t id_processo;

    id_pai = getppid();
    id_processo = getpid();

    printf("Digite: ps -aux | grep pid\n");
    printf("PID:\t %d\n PPID:\t %d\n", id_processo, id_pai);

    return 0;
}
