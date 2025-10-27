#include <iostream>
#include <thread>
#include <queue>
#include <chrono>
#include <condition_variable>
#include <mutex>

const int BUFFER_SIZE = 5;
const int NUM_ITEMS = 20;

class BufferMonitor {
    private:
        std::queue<int> buffer;
        const int max_size;
        std::mutex mtx;
        std::condition_variable not_full;
        std::condition_variable not_empty;

    public:
        BufferMonitor(int size) : max_size(size) {}
        
        void produce(int item, int producer_id) {
            std::unique_lock<std::mutex> lock(mtx);
            
            // Esperar enquanto o buffer estiver cheio
            not_full.wait(lock, [this]() { return buffer.size() < max_size; });
            
            // Inserir item no buffer
            buffer.push(item);
            std::cout << "Produtor " << producer_id << " produziu: " << item 
                    << " (Buffer size: " << buffer.size() << ")\n";
            
            // Notificar consumidores que o buffer não está vazio
            not_empty.notify_one();
        }
        
        int consume(int consumer_id) {
            std::unique_lock<std::mutex> lock(mtx);
            
            // Esperar enquanto o buffer estiver vazio
            not_empty.wait(lock, [this]() { return !buffer.empty(); });
            
            // Remover item do buffer
            int item = buffer.front();
            buffer.pop();
            std::cout << "Consumidor " << consumer_id << " consumiu: " << item 
                    << " (Buffer size: " << buffer.size() << ")\n";
            
            // Notificar produtores que o buffer não está cheio
            not_full.notify_one();
            
            return item;
        }
};

BufferMonitor monitor(BUFFER_SIZE);
int monitor_item_counter = 0;

void monitor_producer(int id) {
    for (int i = 0; i < NUM_ITEMS / 2; ++i) {
        int item = ++monitor_item_counter;
        monitor.produce(item, id);
        
        // Simular tempo de produção
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void monitor_consumer(int id) {
    for (int i = 0; i < NUM_ITEMS / 2; ++i) {
        monitor.consume(id);
        
        // Simular tempo de consumo
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

int main() {
    std::cout << "=== SOLUÇÃO COM MONITOR ===\n";
    
    std::thread prod1(monitor_producer, 1);
    std::thread prod2(monitor_producer, 2);
    std::thread cons1(monitor_consumer, 1);
    std::thread cons2(monitor_consumer, 2);
    
    prod1.join();
    prod2.join();
    cons1.join();
    cons2.join();
    
    std::cout << "Todos os threads completaram!\n\n";

    return 0;
}
