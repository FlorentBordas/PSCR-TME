#ifndef SRC_SOCKET_H_
#define SRC_SOCKET_H_

#include <netinet/ip.h>
#include <string>
#include <iosfwd>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

namespace pr {

class Socket {
	int fd;

public :
	//Valeur par défaut
	Socket():fd(-1){}

	//Constructeur de la socket
	Socket(int fd):fd(fd){}

	// tente de se connecter à l'hôte fourni
	void connect(const std::string & host, int port){
		int sfd;
		struct addrinfo hints;
		struct addrinfo *result;
	
		memset(&hints, 0, sizeof(hints));
		hints.ai_family= AF_UNSPEC;
		hints.ai_socktype= SOCK_STREAM;
		hints.ai_flags= AI_PASSIVE;
		hints.ai_protocol= 0;

		s = getaddrinfo(host, port,&hints, &result);

/*
		for(rp = result; rp != NULL; rp = rp->ai_next){
			sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
			if(sfd)
				continue;

			if(bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
				break;

			close(sfd);
		}

		freeaddrinfo(result);
		*/

		this->fd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
		connect(this->fd,result->ai_addr,result->ai_addrlen);
		freeaddrinfo(result);
	}

	void connect(in_addr ipv4, int port){
		
	}


	bool isOpen() const {return fd != -1;}
	int getFD() { return fd ;}

	void close();
};

std::ostream & operator<< (std::ostream & os	, struct sockaddr_in * addr);

}

#endif /* SRC_SOCKET_H_ */
