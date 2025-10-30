// Exemplo quebrado

#include <cstdio>
#include <thread>
#include <chrono>

using namespace std;

int NUMTHREADS = 4;

void run(int i) {
    for (int j=0; j<5; j++) {
        printf("Thread #%d está executando no núcleo %d\n", i, sched_getcpu());
        this_thread::sleep_for(chrono::seconds (1));
    }
}

int main(int argc, char *argv[]) {
    unsigned int n = thread::hardware_concurrency();
    printf("Minha CPU possui %d núcleos\n", n);
    
    vector<thread> threads;
    
    cpu_set_t cpuset;
    int ret;

    for (int i=0; i< NUMTHREADS; i++) {
        threads.push_back(thread(run, i));
        CPU_ZERO(&cpuset);        // Limpa o conjunto de CPUs
        CPU_SET(i, &cpuset);      // Adiciona CPU 'i' ao conjunto
        // Aplica a afinidade à thread
        ret = pthread_setaffinity_np(threads[i].native_handle(), sizeof(cpu_set_t), &cpuset);
    }
}
