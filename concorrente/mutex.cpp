#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

// TODO: compilar com e sem mutex

std::mutex mtx;

using namespace std;

void print_block(int n, char c) {
    mtx.lock();
    for (int i = 0; i < n; i++) {
        std::cout << c;
        this_thread::sleep_for(chrono::milliseconds(1));
    }
    std::cout << '\n';
    mtx.unlock();
}

int main() {
    thread t1(print_block, 50, '*');
    thread t2(print_block, 50, '$');
    t1.join();
    t2.join();
    return 0;
}
