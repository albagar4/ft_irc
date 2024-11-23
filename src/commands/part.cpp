#include <Client.hpp>
#include <Server.hpp>
#include <ircserv.hpp>

void Server::parsePart(std::string buffer, Client &client) {
    Channel *temp;
    size_t i;
    std::vector<std::string> tokens = split(buffer, ',');
    std::string name, reason;
    try {
        if (buffer.empty()) throw ERR_NEEDMOREPARAMS;
        for (i = 0; i < tokens.size(); i++) {
            try {
                name = tokens[i].substr(0, tokens[i].find(" "));
                reason = tokens[i].substr(tokens[i].find(" ") + 1, tokens[i].size() - 1);
                temp = this->findChannel(name);
                if (!temp) throw ERR_NOSUCHCHANNEL;
                if (temp->isClient(client)) {
                    temp->disconnectClient(client);
                    throw SUCCESS;
                } else
                    throw ERR_NOTONCHANNEL;
            } catch (NUM code) {
                if (code == SUCCESS) {
                    std::string response =
                        ":" + client.getHostname() + " PART " + temp->getName() + "\r\n";
                    // response += " " + reason; TODO: Implement reason for leaving
                    client.setResponse(client.getResponse() + response);
                    temp->updateClients(client, response);  // TODO: Test
                    if (temp->isEmpty()) this->closeChannel(*temp);
                    // If an OP leaves, and there isn't any other OP in the channel
                    // a new OP must be selected
                    // if (temp->getOperators().empty()) {
                    //    temp->addOperator(temp->getClients()[0]);
                    // }
                } else if (code == ERR_NOSUCHCHANNEL)
                    err(ERR_NOSUCHCHANNEL, this->getHostname(), client, name);
                else if (code == ERR_NOTONCHANNEL)
                    err(ERR_NOTONCHANNEL, this->getHostname(), client, temp->getName());
            }
        }
    } catch (NUM code) {
        if (code == ERR_NEEDMOREPARAMS)
            err(ERR_NEEDMOREPARAMS, this->getHostname(), client, "PART");
    }
}
