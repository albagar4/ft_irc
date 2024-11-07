#include <Client.hpp>
#include <Server.hpp>
#include <ircserv.hpp>

std::string sendError(NUM errorCode, std::string clientName) {
    std::ostringstream oss;
    oss << errorCode;

    std::string message = errorMessages[errorCode];
    std::string buffer = oss.str() + " " + clientName + " :" + message;

    return (buffer);
}

void Server::parsePass(std::string buffer, Client &client) {
    ssize_t bytes_send;
    std::string msg;
    bool isEmpty = true;

    client.setHostname();
    std::string test;
    bytes_send = 
    for (unsigned long int i = 0; i < buffer.size(); i++)
        if (buffer[i] != ' ' && buffer[i] != '\t' && buffer[i] != '\0')
            isEmpty = false;
    if (isEmpty == true)
        msg = this->getHostname() + " " + sendError(ERR_NEEDMOREPARAMS, client.getHostname());
    else if (this->getPassword() == buffer && client.getPass() == false) {
        client.setPassword(true);
        return ;
    }
    else if (client.getPass() == true)
        msg = this->getHostname() + " " + sendError(ERR_ALREADYREGISTERED, client.getHostname());
    else
        msg = this->getHostname() + " " + sendError(ERR_PASSWDMISMATCH, client.getHostname());
    bytes_send = send(client.getFd(), msg.c_str(), msg.size(), 0);
    if (bytes_send == -1) print_err("Pass send failed");
}
