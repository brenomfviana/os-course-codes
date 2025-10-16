#include <iostream>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int socket_id = socket(AF_INET, SOCK_STREAM, 0);
    
    sockaddr_in endereco{};
    endereco.sin_family = AF_INET;
    endereco.sin_addr.s_addr = inet_addr("127.0.0.1");
    endereco.sin_port = htons(8080);
    
    bind(socket_id, (sockaddr*) &endereco, sizeof(endereco));
    listen(socket_id, 5);
    
    std::cout << "Servidor - aguardando conexões..." << std::endl;
    
    sockaddr endereco_cliente;
    socklen_t endereco_cliente_size;
    int socket_cliente_id = accept(
        socket_id,
        &endereco_cliente,
        &endereco_cliente_size
    );
    
    char msg[1024]{};
    recv(socket_cliente_id, msg, sizeof(msg), 0);
    std::cout << "Servidor - mensagem recebida: " << msg << std::endl;
    
    std::cout << "Servidor - fechando conexões..." << std::endl;

    close(socket_cliente_id);
    close(socket_id);

    return 0;
}
