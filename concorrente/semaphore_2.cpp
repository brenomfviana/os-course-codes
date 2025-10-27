#include <iostream>
#include <thread>
#include <semaphore>
#include <queue>
#include <chrono>
#include <random>

const int BUFFER_SIZE = 5;
const int NUM_ITEMS = 20;

// Semáforos
std::counting_semaphore<BUFFER_SIZE> empty_slots(BUFFER_SIZE);  // Semáforo para slots vazios
std::counting_semaphore<BUFFER_SIZE> full_slots(0);             // Semáforo para slots cheios
std::binary_semaphore mutex(1);                                 // Semáforo binário para exclusão mútua

std::queue<int> buffer;
int item_counter = 0;

void producer(int id) {
    for (int i = 0; i < NUM_ITEMS / 2; ++i) {
        // Produzir item
        int item = ++item_counter;
        
        // Esperar por slot vazio
        empty_slots.acquire();
        
        // Entrar na região crítica
        mutex.acquire();
        
        // Inserir no buffer
        buffer.push(item);
        std::cout << "Produtor " << id << " produziu: " << item 
                  << " (Buffer size: " << buffer.size() << ")\n";
        
        // Simular tempo de produção
        std::this_thread::sleep_for(std::chrono::seconds(1));
        
        // Sair da região crítica
        mutex.release();
        
        // Sinalizar que há um slot cheio
        full_slots.release();
    }
}

void consumer(int id) {
    for (int i = 0; i < NUM_ITEMS / 2; ++i) {
        // Esperar por slot cheio
        full_slots.acquire();
        
        // Entrar na região crítica
        mutex.acquire();
        
        // Remover do buffer
        int item = buffer.front();
        buffer.pop();
        std::cout << "Consumidor " << id << " consumiu: " << item 
                  << " (Buffer size: " << buffer.size() << ")\n";
        
        // Simular tempo de consumo
        std::this_thread::sleep_for(std::chrono::seconds(2));
        
        // Sair da região crítica
        mutex.release();
        
        // Sinalizar que há um slot vazio
        empty_slots.release();
    }
}

int main() {
    std::cout << "=== SOLUÇÃO COM SEMÁFOROS ===\n";
    
    std::thread prod1(producer, 1);
    std::thread prod2(producer, 2);
    std::thread cons1(consumer, 1);
    std::thread cons2(consumer, 2);
    
    prod1.join();
    prod2.join();
    cons1.join();
    cons2.join();
    
    std::cout << "Todos os threads completaram!\n\n";

    return 0;
}
