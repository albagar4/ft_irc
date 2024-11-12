#include <Client.hpp>
#include <Server.hpp>
#include <ircserv.hpp>
// Mode:
//  + adds the mode
//  - removes the mode
//    i invite only
//    t restricts topic change to op
//    k set/remove channel password
//    o give/take op
//    l set/remove user limit to channel

static char addMode(Channel &channel, char mode, std::vector<std::string> tokens) {
    switch (mode) {
        case 'i':
            channel.setInviteOnly(true);
            return mode;
        case 't':
            channel.setOpTopicOnly(true);  // CHANGE TOPIC
            return mode;
        case 'k':
            if (tokens.size() != 3) throw ERR_NEEDMOREPARAMS;
            channel.setPassword(tokens[2]);
            return mode;
        case 'o': {
            if (tokens.size() != 3) throw ERR_NEEDMOREPARAMS;
            std::vector<Client> clients = channel.getClients();
            std::vector<Client>::iterator it = clients.begin();
            for (; it != clients.end(); it++) {
                if (it->getNick() == tokens[2]) {
                    channel.addOperator(*it);
                    return mode;
                }
            }
            throw ERR_USERNOTINCHANNEL;
            return 0;
        }
        case 'l':
            if (tokens.size() != 3) throw ERR_NEEDMOREPARAMS;
            channel.setUserLimit(atoi(tokens[2].c_str()));
            return mode;
        default:
            throw ERR_UNKNOWNMODE;
            return 0;
    }
}
static char removeMode(Channel &channel, char mode, std::vector<std::string> tokens) {
    switch (mode) {
        case 'i':
            channel.setInviteOnly(false);
            return mode;
        case 't':
            channel.setOpTopicOnly(false);
            return mode;
        case 'k':
            channel.setPassword("");
            return mode;
        case 'o': {
            if (tokens.size() != 3) throw ERR_NEEDMOREPARAMS;
            std::vector<Client> operators = channel.getOperators();
            std::vector<Client>::iterator it = operators.begin();
            for (; it != operators.end(); it++) {
                if (it->getNick() == tokens[2]) {
                    channel.removeOperator(*it);
                    return mode;
                }
            }
            throw ERR_USERNOTINCHANNEL;
            return 0;
        }; break;
        case 'l':
            channel.setUserLimit(99);
            return mode;
        default:
            throw ERR_UNKNOWNMODE;
            return 0;
    }
}

void Server::parseMode(std::string buffer, Client &client) {
    Channel *tempChannel;
    std::vector<std::string> tokens = split(buffer, ' ');

    try {
        if (!tokens.size()) throw ERR_NEEDMOREPARAMS;
        tempChannel = this->findChannel(tokens[0]);
        if (!tempChannel) throw ERR_NOSUCHCHANNEL;
        if (tokens.size() == 1) throw RPL_CHANNELMODEIS;
        if (!tempChannel->isOperator(client)) throw ERR_CHANOPRIVSNEEDED;
        size_t i = 0;
        std::string successfulModes;
        try {
            for (; i < tokens[1].size(); i++) {
                if (tokens[1][i] == '+') {
                    successfulModes = '+';
                    while (++i < tokens[1].size() && tokens[1][i] != '-')
                        successfulModes += addMode(*tempChannel, tokens[1][i], tokens);
                }
                if (tokens[1][i] == '-') {
                    successfulModes = '-';
                    while (++i < tokens[1].size() && tokens[1][i] != '+')
                        successfulModes += removeMode(*tempChannel, tokens[1][i], tokens);
                }
            }
            throw SUCCESS;
        } catch (NUM code) {
            if (code == SUCCESS) {
                client.setResponse(client.getResponse() + ":" + this->getHostname() + " MODE " +
                                   tempChannel->getName() + " " + successfulModes);
                if (tokens.size() == 3) client.setResponse(client.getResponse() + " " + tokens[2]);
                client.setResponse(client.getResponse() + "\r\n");
            } else if (code == ERR_USERNOTINCHANNEL)
                err(ERR_USERNOTINCHANNEL, this->getHostname(), client, tokens[2]);
            else if (code == ERR_UNKNOWNMODE)
                err(ERR_UNKNOWNMODE, this->getHostname(), client, &tokens[1][i]);
            else if (code == ERR_NEEDMOREPARAMS)
                throw ERR_NEEDMOREPARAMS;
        }
    } catch (NUM code) {
        if (code == RPL_CHANNELMODEIS)
            client.setResponse(client.getResponse() + ":" + this->getHostname() + " 324 " +
                               tempChannel->getName() + " " + tempChannel->getModes() + "\r\n");
        else if (code == ERR_NEEDMOREPARAMS)
            err(ERR_NEEDMOREPARAMS, this->getHostname(), client, "MODE");
        else if (code == ERR_NOSUCHCHANNEL)
            err(ERR_NOSUCHCHANNEL, this->getHostname(), client, tokens[0]);
        else if (code == ERR_CHANOPRIVSNEEDED)
            err(ERR_CHANOPRIVSNEEDED, this->getHostname(), client, tempChannel->getName());
    }
}
