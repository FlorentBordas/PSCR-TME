#ifndef SRC_SOCKET_H_
#define SRC_SOCKET_H_

#include <netinet/ip.h>
#include <string>
#include <iosfwd>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <string>

namespace pr {

class Socket {
	int fd;

public :
	//Valeur par défaut
	Socket():fd(-1){}

	//Constructeur de la socket
	Socket(int fd):fd(fd){}

	// tente de se connecter à l'hôte fourni
	void connect(const std::string &host, short port);

    void connect(sockaddr *addr, size_t addr_len);


	bool isOpen() const {
        return fd != -1;
    }

	int getFD() {
        return fd ;
    }

    void close(){
        shutdown(fd, SHUT_RDWR);
        ::close(fd);
    }
};



}

#endif /* SRC_SOCKET_H_ */
