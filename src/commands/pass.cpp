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
    std::string msg;
    bool isEmpty = true;

    client.setHostname();
    std::cout << buffer << std::endl;
    for (unsigned long int i = 0; i < buffer.size(); i++)
        if (buffer[i] != ' ' && buffer[i] != '\t' && buffer[i] != '\0')
            isEmpty = false;
    if (isEmpty == true)
        msg = this->getHostname() + " " + sendError(ERR_NEEDMOREPARAMS, client.getHostname());
    else if (this->getPassword() == buffer && client.getPass() == false)
        client.setPassword(true);
    else if (client.getPass() == true)
        msg = this->getHostname() + " " + sendError(ERR_ALREADYREGISTERED, client.getHostname());
    else
        msg = this->getHostname() + " " + sendError(ERR_PASSWDMISMATCH, client.getHostname());
    client.setResponse(msg);
}
