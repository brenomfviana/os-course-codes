#include <cstdio>
#include <thread>

using namespace std;

void func_1() {
    printf("Sou a Thread 1\n");
}

void func_2(int i) {
    printf("Sou a Thread %d\n", i);
}

int main(int argc, char *argv[]) {
    thread threadA(func_1);
    thread threadB(func_2, 2);

    printf("Sou a Thread main\n");

    // Sincronizando com a thread main
    threadA.join();
    threadB.join();

    printf("Sou a Thread main e vou finalizar.\n");

    return 0;
}
