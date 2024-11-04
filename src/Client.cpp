#include <Client.hpp>

Client::Client(int fd, std::string address) {
	this->fd = fd;
	this->address = address;
}

Client::Client(){}
Client::~Client(){}

int Client::getFd(){return this->fd;}
std::string Client::getAddress(){return this->address;}

void Client::setFd(int fd){this->fd = fd;}
void Client::setAddress(std::string address){this->address = address;}
