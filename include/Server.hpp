#ifndef SERVER_HPP
# define SERVER_HPP

#include "ircserv.hpp"

class Server {
private:
	Server() {};
	std::string password;
	int port;
	int serverSocket;
	sockaddr_in serverAddress;
	pollfd fds[512];
public:
	Server(std::string port, std::string password);
	~Server();
	int &getServerSocket(void);
	int checkConnections(void);
};

#endif