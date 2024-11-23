#include <Client.hpp>
#include <Server.hpp>
#include <ircserv.hpp>

void Server::parseInvite(std::string buffer, Client &client) {
    {
        std::vector<std::string> params = split(buffer, ' ');
        for (size_t i = 0; i < params.size(); i++)
            std::cout << params[i] << std::endl;

        if (params.size() < 2) throw ERR_NEEDMOREPARAMS;
        else if (params.size() > 2) throw ERR_TOOMANYCHANNELS;
        else {
            if (!this->findChannel(params[1])) throw ERR_NOSUCHCHANNEL;
            if (!this->findClient(params[0])) throw ERR_NOSUCHNICK;
            Channel *target_channel = this->findChannel(params[1]);
            Client  *target_client = this->findClient(params[0]);

            if (target_channel->isClient(client) == false) throw ERR_NOTONCHANNEL;
            if (target_channel->isOperator(client) == false) throw ERR_CHANOPRIVSNEEDED;
            if (target_channel->isClient(*target_client) == true) throw ERR_USERONCHANNEL;

            std::string success_message = client.getHostname() + " INVITE " + target_client->getNick() + " :" + target_channel->getName() + "\r\n";
            target_client->setResponse(success_message);
            target_channel.
        }
    }
}
