#include <iostream>
#include <thread>
#include <semaphore>
#include <vector>

// TODO: verificar que na saída apenas 3 threads acessam o recurso por vez

// Semáforo que permite até 3 threads simultaneamente
std::counting_semaphore<3> sem(3);

void tarefa(int id) {
    sem.acquire(); // Operação P - decrementa o semáforo
    
    std::cout << "Thread " << id << " entrou na região crítica\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Thread " << id << " saindo da região crítica\n";
    
    sem.release(); // Operação V - incrementa o semáforo
}

int main() {
    std::vector<std::thread> threads;
    
    // Cria 10 threads tentando acessar o recurso
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back(tarefa, i);
    }
    
    // Aguarda todas as threads terminarem
    for (auto &t : threads) {
        t.join();
    }
    
    return 0;
}
