#include <cstdio>
#include <thread>
#include <chrono>

using namespace std;

class Trabalhador {
    public:
        void faz_trabalho();
};

void Trabalhador::faz_trabalho() {
    this_thread::sleep_for(chrono::seconds(1));
    printf("Sou o objeto trabalhador, fui executado pela thread A\n");
}

int main(int argc, char *argv[]) {
    Trabalhador trabalhador;

    thread threadA(&Trabalhador::faz_trabalho, &trabalhador);

    printf("Sou a Thread main\n");

    // Sincronizando com a thread main
    threadA.join();

    printf("Sou a Thread main e vou finalizar.\n");

    return 0;
}
