#include <Client.hpp>
#include <Server.hpp>
#include <ircserv.hpp>

static std::string sendError(NUM errorCode, std::string clientName) {
    std::ostringstream oss;
    oss << errorCode;

    std::string message = errorMessages[errorCode];
    std::string buffer = oss.str() + " " + clientName + " :" + message + "\r\n";

    return (buffer);
}

bool isEmpty(std::string buffer) {
    for (unsigned long int i = 0; i < buffer.size(); i++)
        if (buffer[i] != ' ' && buffer[i] != '\t' && buffer[i] != '\0')
            return (false);
    return (true);
}

void Server::parsePass(std::string buffer, Client &client) {
    std::string msg;
    client.setHostname();
    
    if (this->getPassword() == buffer && client.getPass() == false)
        client.setPassword(true);
    else if (client.getPass() == true)
        msg = this->getHostname() + " " + sendError(ERR_ALREADYREGISTERED, client.getHostname());
    else if (isEmpty(buffer) == true)
        msg = this->getHostname() + " " + sendError(ERR_NEEDMOREPARAMS, client.getHostname());
    else {
        msg = this->getHostname() + " " + sendError(ERR_PASSWDMISMATCH, client.getHostname());
        client.setRetries(client.getRetries() - 1);

        std::stringstream ss;
        ss << client.getRetries();
        msg += "Nbr of retries left: " + ss.str() + "\r\n";
    }

    client.setResponse(msg);

    if (client.getRetries() == 0) {
        sendResponse();
        this->disconnectClient(client);
    }
}
