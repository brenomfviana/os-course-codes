#include <cstdio>
#include <thread>

using namespace std;

void func_1(int &x) {
    printf("Sou a Thread 1 - Contador: %d\n", x++);
}

void func_2(int &x) {
    printf("Sou a Thread 2 - Contador: %d\n", x++);
}

int main(int argc, char *argv[]) {
    int id = 2;

    thread threadA(func_1, ref(id));
    thread threadB(func_2, ref(id));

    printf("Sou a Thread main\n");

    // Sincronizando com a thread main
    threadA.join();
    threadB.join();

    printf("Sou a Thread main e vou finalizar.\n");

    return 0;
}
