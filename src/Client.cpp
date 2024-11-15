#include <Client.hpp>

Client::Client(int fd, sockaddr_in address) {
    this->fd = fd;
    this->address = address;
    this->address_len = sizeof(this->address);
    this->auth = false;
    this->password = false;
    this->nick = "";
    this->user = "";
    if (getpeername(this->fd, (struct sockaddr*)&this->address, &this->address_len) == -1)
        print_err("Unable to source hostname");
    this->host = gethostbyaddr(&this->address.sin_addr, sizeof(this->address.sin_addr), AF_INET);
    this->hostname = "";
    this->incomingMessage = "";
}

Client::Client() {}
Client::~Client() {}

int Client::getFd() const { return this->fd; }
sockaddr_in Client::getAddress() const { return this->address; }
bool Client::getAuth() const { return (this->auth); }
bool Client::getPass() const { return (this->password); }
std::string Client::getNick() const { return (this->nick); }
std::string Client::getUser() const { return (this->user); }
hostent* Client::getHost() const { return (this->host); }
std::string Client::getHostname() const { return (this->hostname); }
std::string Client::getResponse() const { return (this->response); }
std::string Client::getIncomingMessage() const { return (this->incomingMessage); }

void Client::setFd(int fd) { this->fd = fd; }
void Client::setAddress(sockaddr_in address) { this->address = address; }
void Client::setPassword(bool password) { this->password = password; }
void Client::setAuth(bool auth) { this->auth = auth; }
void Client::setNick(std::string nick) { this->nick = nick; }
void Client::setUser(std::string user) { this->user = user; }
void Client::setHostname() {
    this->hostname = this->nick + "!" + this->user + "@" + this->host->h_name;
}
void Client::setResponse(std::string response) { this->response = response; }
void Client::setIncomingMessage(std::string message) { this->incomingMessage = message; }

std::ostream& operator<<(std::ostream& os, const Client& client) {
    os << "Client " << client.getHost()->h_name << " in socket " << client.getFd();
    return (os);
}
