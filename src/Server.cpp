#include <Server.hpp>

Server::Server(std::string port, std::string password): password(password) {
	ft_print("IRC CONSTRUCTOR CALLED");
	this->port = atoi(port.c_str());
	for (unsigned long int i = 0; i < password.size(); i++) {
		if (!isalnum(password[i])) {
			std::cerr << "Password only accepts alphanumeric characters" << std::endl;
			exit (1);
		}
	}
	this->serverSocket = socket(AF_INET, SOCK_STREAM, 0);

	// Especificaciones de la dirección
	this->serverAddress.sin_family = AF_INET;
	this->serverAddress.sin_port = htons(this->port);
	this->serverAddress.sin_addr.s_addr = INADDR_ANY;

	// Hace que se repita el proceso
	if (fcntl(serverSocket, F_SETFL, O_NONBLOCK) == -1)
		; //error

	bind(this->serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
	listen(serverSocket, 5);
}

Server::~Server() { close(this->serverSocket); }

int &Server::getServerSocket(void) {
	return (this->serverSocket);
}

int Server::checkConnections(void) {
	int result = poll(this->fds, 512, 0);
	if (result == -1)
		; //throw error
	return (result);
}
