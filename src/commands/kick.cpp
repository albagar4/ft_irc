#include <Client.hpp>
#include <Server.hpp>
#include <ircserv.hpp>
void Server::parseKick(std::string buffer, Client &client) {
    Channel *temp;
    std::vector<std::string> tokens = split(buffer, ' ');
    try {
        if (!tokens.size()) throw ERR_NEEDMOREPARAMS;
        if (tokens.size() < 2 || tokens[0].empty() || tokens[1].empty()) throw ERR_NEEDMOREPARAMS;
        temp = this->findChannel(tokens[0]);
        if (!temp) throw ERR_NOSUCHCHANNEL;
        if (!temp->isOperator(client)) throw ERR_CHANOPRIVSNEEDED;
        std::vector<std::string> names = split(tokens[1], ',');
        for (size_t i = 0; i < names.size(); i++) {
            try {
                Client *clientToKick = this->findClient(names[i]);
                if (!clientToKick) throw ERR_NOSUCHNICK;
                if (temp->isClient(*clientToKick)) {
                    temp->disconnectClient(*clientToKick);
                    throw SUCCESS;
                } else
                    throw ERR_USERNOTINCHANNEL;
            } catch (NUM code) {
                if (code == SUCCESS) {
                    std::string response =
                        ":" + client.getHostname() + " KICK " + temp->getName() + " " + names[i];
                    if (tokens.size() > 2 && !tokens[2].empty()) response += " " + tokens[2];
                    response += "\r\n";
                    client.setResponse(client.getResponse() + response);
                    temp->updateClients(client, response);  // TODO: Test
                } else if (code == ERR_NOSUCHNICK)
                    err(ERR_NOSUCHNICK, this->getHostname(), client, names[i]);
                else if (code == ERR_USERNOTINCHANNEL)
                    err(ERR_USERNOTINCHANNEL, this->getHostname(), client,
                        names[i] + " " + temp->getName());
            }
        }
    } catch (NUM code) {
        if (code == ERR_NEEDMOREPARAMS)
            err(ERR_NEEDMOREPARAMS, this->getHostname(), client, "KICK");
        else if (code == ERR_NOSUCHCHANNEL)
            err(ERR_NOSUCHCHANNEL, this->getHostname(), client, tokens[0]);
        else if (code == ERR_CHANOPRIVSNEEDED)
            err(ERR_CHANOPRIVSNEEDED, this->getHostname(), client, temp->getName());
    }
}
