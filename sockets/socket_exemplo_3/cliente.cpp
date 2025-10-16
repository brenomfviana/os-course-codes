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
    
    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(8080);

    std::cout << "Cliente - conectando ao servidor..." << std::endl;
    
    connect(socket_id, (sockaddr*)&server_address, sizeof(server_address));
    
    std::cout << "Cliente - enviando mensagem ao servidor..." << std::endl;

    Mensagem msg{};
    msg.id = 1;
    msg.tipo = 10;
    strcpy(msg.texto, "Olá servidor 4!");

    send(socket_id, &msg, sizeof(msg), 0);
    
    std::cout << "Cliente - fechando conexões..." << std::endl;
    
    close(socket_id);
    return 0;
}
