#include <Client.hpp>
#include <Server.hpp>
#include <ircserv.hpp>

void Server::parseInvite(std::string buffer, Client &client) {
    std::vector<std::string> params = split(buffer, ' ');
    try {
        if (buffer.empty() || params.size() < 2)
            throw ERR_NEEDMOREPARAMS;
        else if (params.size() > 2)
            throw ERR_UNKNOWNCOMMAND;
        else {
            if (!this->findChannel(params[1])) throw ERR_NOSUCHCHANNEL;
            if (!this->findClient(params[0])) throw ERR_NOSUCHNICK;
            Channel *target_channel = this->findChannel(params[1]);
            Client *target_client = this->findClient(params[0]);

            if (target_channel->isClient(client) == false) throw ERR_NOTONCHANNEL;
            if (target_channel->isOperator(client) == false) throw ERR_CHANOPRIVSNEEDED;
            if (target_channel->isClient(*target_client) == true) throw ERR_USERONCHANNEL;

            target_channel->addInvited(*target_client);
            std::string success_message = ":" + client.getHostname() + " INVITE " +
                                          target_client->getNick() + " :" +
                                          target_channel->getName() + "\r\n";
            target_client->setResponse(success_message);
            client.setResponse(success_message);
        }
    } catch (NUM error) {
        if (error == ERR_NEEDMOREPARAMS) err(ERR_NEEDMOREPARAMS, this->getHostname(), client);
        if (error == ERR_UNKNOWNCOMMAND)
            err(ERR_UNKNOWNCOMMAND, this->getHostname(), client, buffer);
        if (error == ERR_NOSUCHCHANNEL)
            err(ERR_NOSUCHCHANNEL, this->getHostname(), client, params[1]);
        if (error == ERR_NOSUCHNICK) err(ERR_NOSUCHNICK, this->getHostname(), client, params[0]);
        if (error == ERR_NOTONCHANNEL)
            err(ERR_NOTONCHANNEL, this->getHostname(), client, params[1]);
        if (error == ERR_CHANOPRIVSNEEDED)
            err(ERR_CHANOPRIVSNEEDED, this->getHostname(), client, params[1]);
        if (error == ERR_USERONCHANNEL)
            err(ERR_USERONCHANNEL, this->getHostname(), client, params[0] + " " + params[1]);
    }
}
