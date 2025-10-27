#include <cstdio>
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void handle(int i) {
    this_thread::sleep_for(chrono::seconds(1));
    printf("Sou a Thread %d\n", i);
}

int main(int argc, char *argv[]) {
    thread threadA(handle, 1);
    thread::id threadA_id = threadA.get_id();

    thread threadB(handle, 2);
    thread::id threadB_id = threadB.get_id();

    cout << "ID da Thread main é: " << this_thread::get_id() << endl;
    cout << "ID da Thread 1 é: " << threadA_id << endl;
    cout << "ID da Thread 2 é: " << threadB_id << endl;

    // Sincronizando com a thread main
    threadA.detach();
    threadB.detach();

    printf("Sou a Thread main e vou finalizar.\n");

    return 0;
}
