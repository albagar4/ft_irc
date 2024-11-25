#include <Client.hpp>
#include <Server.hpp>
#include <ircserv.hpp>

static std::string rpl_NamReply(Server &server, Client &client, Channel &channel) {
    std::string response = ":" + server.getHostname() + " 353 ";
    response += client.getNick() + " ";
    response += "= ";
    response += channel.getName() + " :";
    response += channel.getUserList();
    response += "\r\n";
    return response;
}
static std::string rpl_EndOfNames(Server &server, Client &client, Channel &channel) {
    std::string response = ":" + server.getHostname() + " 366 ";
    response += client.getNick() + " ";
    response += channel.getName() + " :";
    response += "End of /NAMES list.";
    response += "\r\n";
    return response;
}
static std::string rpl_Topic(Server &server, Client &client, Channel &channel) {
    std::string response = ":" + server.getHostname() + " 332 ";
    response += client.getNick() + " ";
    response += channel.getName() + " :";
    response += channel.getTopic();
    response += "\r\n";
    return response;
}
static std::string rpl_Successful(Server &server, Client &client, Channel &channel) {
    std::string response = ":" + client.getHostname();
    response += " JOIN :";
    response += channel.getName();
    response += "\r\n";
    channel.updateClients(client, response);
    if (channel.getTopic() != "") response += rpl_Topic(server, client, channel);
    response += rpl_NamReply(server, client, channel);
    response += rpl_EndOfNames(server, client, channel);
    return response;
}

void Server::parseJoin(std::string buffer, Client &client) {
    Channel *temp;
    try {
        if (buffer.empty()) throw ERR_NEEDMOREPARAMS;
        std::vector<std::string> tokens = split(buffer, ',');
        std::vector<std::string> nameKey;
        for (size_t i = 0; i < tokens.size(); i++) {
            try {
                size_t colonPos = tokens[i].find_first_of(":");
                std::string topic = tokens[i].substr(colonPos + 1, tokens[i].size());
                if (topic != tokens[i]) {
                    tokens[i] = tokens[i].substr(0, colonPos - 1);
                } else {
                    topic = "";
                }
                nameKey = split(tokens[i], ' ');
                if (nameKey[0][0] != '#') throw ERR_UNKNOWNCOMMAND;
                if (isNewChannel(nameKey[0]) == true) {
                    Channel newChannel(nameKey[0], topic);
                    newChannel.addClient(client);
                    newChannel.setServer(this);
                    this->channels.push_back(newChannel);
                } else {
                    temp = this->findChannel(nameKey[0]);
                    if (temp->isClient(client)) break;
                    if (temp->getClients().size() >= (size_t)temp->getUserLimit())
                        throw ERR_CHANNELISFULL;
                    if (temp->getInviteOnly() == true && !temp->isInvited(client))
                        throw ERR_INVITEONLYCHAN;
                    if (!temp->isInvited(client) && !temp->getPassword().empty()) {
                        if (nameKey.size() > 1) {
                            if (nameKey[1] != temp->getPassword()) throw ERR_BADCHANNELKEY;
                        } else
                            throw ERR_BADCHANNELKEY;
                    }
                    temp->addClient(client);
                    temp->removeInvited(client);
                }
                throw SUCCESS;
            } catch (NUM code) {
                if (code == SUCCESS)
                    client.setResponse(
                        client.getResponse() +
                        rpl_Successful(*this, client, *this->findChannel(nameKey[0])));
                else if (code == ERR_CHANNELISFULL)
                    err(ERR_CHANNELISFULL, this->getHostname(), client, temp->getName());
                else if (code == ERR_INVITEONLYCHAN)
                    err(ERR_INVITEONLYCHAN, this->getHostname(), client, temp->getName());
                else if (code == ERR_BADCHANNELKEY)
                    err(ERR_BADCHANNELKEY, this->getHostname(), client, temp->getName());
                else if (code == ERR_UNKNOWNCOMMAND)
                    err(ERR_UNKNOWNCOMMAND, this->getHostname(), client, nameKey[0]);
            }
        }
    } catch (NUM code) {
        if (code == ERR_NEEDMOREPARAMS)
            err(ERR_NEEDMOREPARAMS, this->getHostname(), client, "JOIN");
    }
}
