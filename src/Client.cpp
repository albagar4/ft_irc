/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagar4 <albagar4@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:30:06 by albagar4          #+#    #+#             */
/*   Updated: 2024/11/27 11:30:08 by albagar4         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Client.hpp>

Client::Client(int fd, sockaddr_in address) {
    this->fd = fd;
    this->address = address;
    this->address_len = sizeof(this->address);
    this->auth = false;
    this->password = false;
    this->nick = "";
    this->user = "";
    this->realname = "";
    if (getpeername(this->fd, (struct sockaddr*)&this->address, &this->address_len) == -1)
        print_err("Unable to source hostname");
    this->host = gethostbyaddr(&this->address.sin_addr, sizeof(this->address.sin_addr), AF_INET);
    this->hostname = "";
    this->incomingMessage = "";
    this->retries = 3;
    this->response = "";
}

Client::Client() { this->fd = 0; }
Client::~Client() {}

int Client::getFd() const { return this->fd; }
sockaddr_in Client::getAddress() const { return this->address; }
bool Client::getAuth() const { return (this->auth); }
bool Client::getPass() const { return (this->password); }
std::string Client::getNick() const { return (this->nick); }
std::string Client::getUser() const { return (this->user); }
std::string Client::getRealname() const { return (this->realname); }
hostent* Client::getHost() const { return (this->host); }
std::string Client::getHostname() const { return (this->hostname); }
std::string Client::getResponse() const { return (this->response); }
std::string Client::getIncomingMessage() const { return (this->incomingMessage); }
int Client::getRetries() const { return (this->retries); }

void Client::setFd(int fd) { this->fd = fd; }
void Client::setAddress(sockaddr_in address) { this->address = address; }
void Client::setPassword(bool password) { this->password = password; }
void Client::setAuth(bool auth) { this->auth = auth; }
void Client::setNick(std::string nick) { this->nick = nick; }
void Client::setUser(std::string user) { this->user = user; }
void Client::setRealname(std::string realname) { this->realname = realname; }
void Client::setHostname() {
    this->hostname = this->nick + "!" + this->user + "@" + this->host->h_name;
}
void Client::setResponse(std::string response) { this->response = response; }
void Client::setIncomingMessage(std::string message) { this->incomingMessage = message; }
void Client::setRetries(int retry) { this->retries = retry; }

std::ostream& operator<<(std::ostream& os, const Client& client) {
    os << "Client " << client.getHost()->h_name << " in socket " << client.getFd();
    return (os);
}
