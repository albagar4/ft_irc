#include <Client.hpp>

Client::Client(int fd, std::string address) {
    this->fd = fd;
    this->address = address;
}

Client::Client() {}
Client::~Client() {}

int Client::getFd() const { return this->fd; }
std::string Client::getAddress() const { return this->address; }

void Client::setFd(int fd) { this->fd = fd; }
void Client::setAddress(std::string address) { this->address = address; }

std::ostream& operator<<(std::ostream& os, const Client& client) {
    os << "Client " << client.getAddress() << " in socket " << client.getFd();
    return (os);
}
