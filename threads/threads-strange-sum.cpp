#include <cstdio>
#include <thread>
#include <chrono>

using namespace std;

void strange_sum(int &x, int id) {
    for (int i = 0; i < 5; i++) {
        --x;
        this_thread::sleep_for(chrono::seconds(1));
        ++x;
        if (x != 10) {
            printf("Thread %d - O valor de x é %d\n", id, x);
        }
    }
}

int main(int argc, char *argv[]) {
    int valor = 10;
    
    thread threadA (strange_sum, ref(valor), 1);
    thread threadB (strange_sum, ref(valor), 2);
    
    printf("Sou a Thread main\n");
    
    threadA.join();
    threadB.join();
    
    printf("Sou a Thread main e vou finalizar.\n");
    
    return 0;
}
