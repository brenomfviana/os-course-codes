#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

struct Mensagem {
    int id;
    char texto[1024];
    int tipo;
};

int main() {
    int socket_id = socket(AF_INET, SOCK_STREAM, 0);
    
    sockaddr_in endereco_servidor{};
    endereco_servidor.sin_family = AF_INET;
    endereco_servidor.sin_addr.s_addr = inet_addr("127.0.0.1");
    endereco_servidor.sin_port = htons(8080);

    std::cout << "Cliente - conectando ao servidor..." << std::endl;
    
    connect(socket_id, (sockaddr*) &endereco_servidor, sizeof(endereco_servidor));
    
    std::cout << "Cliente - enviando mensagem ao servidor..." << std::endl;

    Mensagem msg{};
    msg.id = 1;
    msg.tipo = 10;
    strcpy(msg.texto, "Olá servidor!");

    send(socket_id, &msg, sizeof(msg), 0);
    
    std::cout << "Cliente - fechando conexões..." << std::endl;
    
    close(socket_id);

    return 0;
}
