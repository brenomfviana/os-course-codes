#include <iostream>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <thread>

struct Mensagem {
    int id;
    char texto[1024];
    int tipo;
};

void tratar_cliente(int socket_cliente_id) {
    std::cout << "Servidor - conexão estabelecida..." << std::endl;
    Mensagem msg{};
    recv(socket_cliente_id, &msg, sizeof(msg), 0);
    std::cout << "Servidor Thread " << std::this_thread::get_id() 
              << "\nServidor - mensagem recebida - ID: " << msg.id 
              << ", Texto: " << msg.texto 
              << ", Tipo: " << msg.tipo << std::endl;
    std::cout << "Servidor - fechando conexão..." << std::endl;
    sleep(5);
    close(socket_cliente_id);
}

int main() {
    int socket_id = socket(AF_INET, SOCK_STREAM, 0);
    
    sockaddr_in endereco{};
    endereco.sin_family = AF_INET;
    endereco.sin_addr.s_addr = inet_addr("127.0.0.1");
    endereco.sin_port = htons(8080);
    
    bind(socket_id, (sockaddr*) &endereco, sizeof(endereco));
    listen(socket_id, 5);
    
    std::cout << "Servidor - aguardando conexões..." << std::endl;
    
    while (true) {
        int socket_cliente_id = accept(socket_id, nullptr, nullptr);
        if (socket_cliente_id != -1) {
            std::cout << "Servidor - conexão aceita" << std::endl;
        }
        std::thread(tratar_cliente, socket_cliente_id).detach();
    }
    
    close(socket_id);

    return 0;
}
