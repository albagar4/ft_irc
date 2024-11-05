#include <Server.hpp>

void Server::createServerSocket() {
    // Crear el socket del servidor
    this->serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (this->serverSocket == -1) print_err("Unable to create server socket");

    int optval = 1;
    if (setsockopt(this->serverSocket, SOL_SOCKET, SO_REUSEADDR, &optval,
                   sizeof(optval)) == -1)
        print_err("Unable to set options to server socket");

    // Especificaciones de la dirección
    this->serverAddress.sin_family = AF_INET;
    this->serverAddress.sin_port = htons(this->port);
    this->serverAddress.sin_addr.s_addr = INADDR_ANY;

    // Hace que se repita el proceso
    if (fcntl(serverSocket, F_SETFL, O_NONBLOCK) == -1)
        print_err("Unable to set server socket as non blocking");

    // Vincula el fd del servidor a una dirección
    if (bind(this->serverSocket, (struct sockaddr*)&serverAddress,
             sizeof(serverAddress)))
        print_err("Unable to bind server socket");

    // Permite que el servidor escuche conexiones
    if (listen(serverSocket, 5) == -1)
        print_err("Unable to listen server socket");

    struct pollfd newPoll;

    newPoll.fd = this->serverSocket;
    newPoll.events = POLLIN;
    newPoll.revents = 0;
    fds.push_back(newPoll);
}

static int parsePort(std::string port) {
    if (port.find_first_not_of("0123456789") != std::string::npos)
        print_err("Port number is invalid");
    return (atoi(port.c_str()));
}

static std::string parsePassword(std::string password) {
    for (unsigned long int i = 0; i < password.size(); i++) {
        if (!isalnum(password[i]))
            print_err("Password only accepts alphanumeric characters");
    }
    return (password);
}

Server::Server(std::string port, std::string password) {
    ft_print(ASCII_ART);
    ft_print("IRC CONSTRUCTOR CALLED");
    this->port = parsePort(port);
    this->password = parsePassword(password);

    this->setAuthFunctions();
    this->setCmdFunctions();
    createServerSocket();
}

Server::~Server() { close(this->serverSocket); }

void Server::setAuthFunctions(void) {
    this->authentification[0] = &Server::parseCap;
    this->authentification[1] = &Server::parsePass;
    this->authentification[2] = &Server::parseNick;
    this->authentification[3] = &Server::parseUser;
}

void Server::setCmdFunctions(void) {
    this->commands[0] = &Server::parseJoin;
    this->commands[1] = &Server::parsePart;
    this->commands[2] = &Server::parseKick;
    this->commands[3] = &Server::parseInvite;
    this->commands[4] = &Server::parseTopic;
    this->commands[5] = &Server::parseMode;
    this->commands[6] = &Server::parsePrivMsg;
    this->commands[7] = &Server::parseQuit;
}

int Server::getServerSocket(void) const { return (this->serverSocket); }
int Server::getPort(void) const { return (this->port); }
std::string Server::getPassword(void) const { return (this->password); }
std::map<int, Client> Server::getMap(void) const { return (this->map); }

int Server::checkConnections(void) {
    int result = poll(&this->fds[0], fds.size(), 0);
    if (result == -1) print_err("Error while trying to poll()");
    return (result);
}

int Server::iterateFds(void) {
    unsigned long int i = 0;

    for (; i < this->fds.size(); i++) {
        // Miramos si hay respuesta y esa respuesta es POLLIN
        if (fds[i].revents & POLLIN) {
            if (fds[i].fd == this->serverSocket)
                this->newConnection();
            else
                this->manageUpdates(this->map[fds[i].fd]);
        }
    }
    return (i);
}

void Server::newConnection() {
    sockaddr_in address;
    socklen_t length = sizeof(address);

    int clientSocket =
        accept(this->getServerSocket(), (sockaddr*)&address, &length);
    if (clientSocket == -1) exit(1);
    if (fcntl(clientSocket, F_SETFL, O_NONBLOCK) == -1) exit(1);

    Client client(clientSocket, inet_ntoa(address.sin_addr));
    this->map[clientSocket] = client;

    pollfd poll;
    poll.fd = clientSocket;
    poll.events = POLLIN;
    poll.revents = 0;
    this->fds.push_back(poll);

    std::cout << client << std::endl;
}

void Server::manageUpdates(Client& client) {
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));

    ssize_t bytes = recv(client.getFd(), buffer, sizeof(buffer) - 1, 0);
    if (bytes == -1) print_err("recv has failed");
    if (bytes == 0) this->disconnectClient(client);
    if (bytes > 0) this->parseCommands(buffer, client);
}

void Server::parseCommands(char* buffer, Client& client) {
    std::string buff(buffer);
    std::string title = buff.substr(0, buff.find(" "));
    if (client.getAuth() == false) {
        std::string commandArray[4] = {"CAP", "PASS", "NICK", "USER"};
        for (int i = 0; i < 4; i++) {
            if (title == commandArray[i]) {
                (this->*authentification[i])(
                    buff.substr(buff.find(" ") + 1).c_str(), client);
                return;
            }
        }
        // enviar mensaje de no autentificacion con pasos a seguir
    } else {
        std::string commandArray[8] = {"JOIN",  "PART", "KICK",    "INVITE",
                                       "TOPIC", "MODE", "PRIVMSG", "QUIT"};
        for (int i = 0; i < 4; i++) {
            if (title == commandArray[i]) {
                (this->*commands[i])(buff.substr(buff.find(" ") + 1).c_str(),
                                     client);
                return;
            }
        }
        // mensaje con la lista de usos y comandos disponibles
    }
}

void Server::disconnectClient(Client& client) {
    int temp = client.getFd();
    for (std::vector<pollfd>::iterator it = this->fds.begin();
         it != this->fds.end(); it++) {
        if (temp == it->fd) {
            this->fds.erase(it);
            this->map.erase(temp);
            close(temp);
            std::cout << "Client in socket " << temp << " was disconnected"
                      << std::endl;
            break;
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Server& server) {
    os << "* Server information *";
    os << "\nPassword: " << server.getPassword();
    os << "\nPort: " << server.getPort();
    os << "\nSocket: " << server.getServerSocket();
    os << "\nCurrent amount of clients: " << server.getMap().size();
    return (os);
}
