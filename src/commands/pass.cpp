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

//client es getHostName
void Server::parsePass(std::string buffer, Client &client) {
    ssize_t bytes_send;
    std::string msg;

    if (buffer.empty())
        msg = this->getHostname() + " " + sendError(ERR_NEEDMOREPARAMS, client.getHostName());
    else if (this->getPassword() == buffer && client.getPass() == false) {
        client.setPassword(true);
        return ;
    }
    else if (this->getPassword() == buffer && client.getPass() == true)
        msg = this->getHostname() + " " + sendError(ERR_ALREADYREGISTERED, client.getHostName());
    else
        msg = this->getHostname() + " " + sendError(ERR_PASSWDMISMATCH, client.getHostName());
    bytes_send = send(client.getFd(), msg.c_str(), msg.size(), 0);
    if (bytes_send == -1) print_err("Pass send failed");
}
