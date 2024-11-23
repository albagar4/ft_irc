#include <Client.hpp>
#include <Server.hpp>
#include <ircserv.hpp>

bool noParams(std::string buffer) {
    std::vector<std::string> params = split(buffer, ' ');

    if (params.size() == 4 && params[1] == "0" && params[2] == "*")
        return (false);
    return (true);
}

bool correctChars(std::string params, int sign) {
    if (params.size() > 9) return (false);

    for (unsigned long int i = 0; i < params.size(); i++) {
        if (params.empty() || !isalnum(params[i])) {
            if (params.empty()) return (false);
            if (sign == 0 && params[i] == ' ') return (false);
            if (params[i] != '-' && params[i] != '.' && params[i] != '_') return (false);
        }
        else if (isdigit(params[0])) return (false);
    }

    return (true);
}

void Server::parseUser(std::string buffer, Client &client) {
    try {
        if (buffer.empty() || noParams(buffer) == true) throw ERR_NEEDMOREPARAMS;

        std::vector<std::string> params = split(buffer, ' ');
        if (!client.getUser().empty()) throw ERR_ALREADYREGISTERED;
        else {
            if (client.getNick().empty() || correctChars(params[0], 0) == false || correctChars(params[3], 1) == false)
                throw ERR_NOTREGISTERED;
            client.setUser(params[0]);
            client.setRealname(params[3]);
        }
        client.setHostname();
        client.setAuth(true);
    }
    catch (NUM code) {
        client.setHostname();

        if (code == ERR_NEEDMOREPARAMS)
            err(ERR_NEEDMOREPARAMS, this->getHostname(), client, buffer);
        if (code == ERR_ALREADYREGISTERED)
            err(ERR_ALREADYREGISTERED, this->getHostname(), client);
        if (code == ERR_NOTREGISTERED) {
            err(ERR_NOTREGISTERED, this->getHostname(), client);
            if (client.getNick() == "")
                client.setResponse(client.getResponse() + "NICK must be setted before USER\r\n");
            else
                client.setResponse(client.getResponse() + "Invalid characters were found\r\n");
        }
    }
}
