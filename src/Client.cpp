#include <Client.hpp>

Client::Client(int fd, std::string address) {
    this->fd = fd;
    this->address = address;
    this->auth = false;
    this->password = false;
    this->nick = "";
    this->user = "";
}

Client::Client() {}
Client::~Client() {}

int Client::getFd() const { return this->fd; }
std::string Client::getAddress() const { return this->address; }
bool Client::getAuth() const { return (this->auth); }
bool Client::getPass() const { return (this->password); }
std::string Client::getNick() const { return (this->nick); }
std::string Client::getUser() const { return (this->user); }

void Client::setFd(int fd) { this->fd = fd; }
void Client::setAddress(std::string address) { this->address = address; }
void Client::setPassword(bool password) { this->password = password; }
void Client::setAuth(bool auth) { this->auth = auth; }
void Client::setNick(std::string nick) { this->nick = nick; }
void Client::setUser(std::string user) { this->user = user; }

std::ostream& operator<<(std::ostream& os, const Client& client) {
    os << "Client " << client.getAddress() << " in socket " << client.getFd();
    return (os);
}
