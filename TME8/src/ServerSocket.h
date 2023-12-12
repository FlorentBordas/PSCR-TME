#ifndef SRC_SERVERSOCKET_H_
#define SRC_SERVERSOCKET_H_

#include "Socket.h"

namespace pr {
    class ServerSocket {
        int socketfd;

    public :
        //Démarre l'écoute sur le port donné

        ServerSocket(int port){
            int fd = socket(AF_INET6, SOCK_STREAM, 0);
            if(fd == -1){
                perror("Création socket");
                exit(EXIT_FAILURE);
            }

            struct sockaddr_in sin;
            sin.sin_family = AF_INET6;
            sin.sin_port = htons(port);
            sin.sin_addr.s_addr = INADDR_ANY; //Mask 0.0.0.0

            if(bind(fd, (struct sockaddr *) &sin, sizeof(sin))){
                ::close(socketfd);
            }

            listen(fd, 50);
            socketfd = fd;
        }
        int getF(){return socketfd;}
        bool isOpen() const {return socketfd != -1;}

        Socket accept(){
            int clientfd = ::accept(socketfd, 0,0);
            struct sockaddr addr;
            socklen_t len = sizeof(addr);
            if((clientfd = ::accept(socketfd, &addr, &len)) < 0){
                perror("Erreur accept serveur");
            }
            return clientfd;
        }
        void close();
    };
} // ns pr
#endif /* SRC_SERVERSOCKET_H_ */
