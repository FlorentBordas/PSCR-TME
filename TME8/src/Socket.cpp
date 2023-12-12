//
// Created by floflo on 12/8/23.
//

#include "Socket.h"

void Socket::connect(const std::string &host, short port){
    struct addrinfo hints;
    struct addrinfo *result;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family= AF_UNSPEC;
    hints.ai_socktype= SOCK_STREAM;
    hints.ai_flags= AI_PASSIVE;
    hints.ai_protocol= 0;

    if(getaddrinfo(host.c_str(), to_string(port).c_str(),&hints, &result)) {
        perror("erreur getaddrinfo socket.h");
    }

    fd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if(fd < 0){
        perror("création socket socket.h");
    }
    

    freeaddrinfo(result);
}

void Socket::connect(sockaddr *addr, size_t addr_len){
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0) {
        perror("Création socket");
    }

    if(::connect(fd, addr, addr_len) < 0){
        perror("Erreur Connexion");
    }
}