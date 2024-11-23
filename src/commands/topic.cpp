#include <Client.hpp>
#include <Server.hpp>
#include <ircserv.hpp>

static std::string rpl_NoTopic(Server &server, Client &client, Channel &channel) {
    std::string response = ":" + server.getHostname() + " 331 ";
    response += client.getNick();
    response += " ";
    response += channel.getName();
    response += " :No topic is set";
    response += "\r\n";
    return response;
}

static std::string rpl_Topic(Server &server, Client &client, Channel &channel) {
    std::string response = ":" + server.getHostname() + " 332 ";
    response += client.getNick();
    response += " ";
    response += channel.getName();
    response += " :" + channel.getTopic();
    response += "\r\n";
    return response;
}

static std::string rpl_Successful(Client &client, Channel &channel) {
    std::string response = ":" + client.getHostname();
    response += " TOPIC ";
    response += channel.getName();
    response += " :" + channel.getTopic();
    response += "\r\n";
    return response;
}

void Server::parseTopic(std::string buffer, Client &client) {
    Channel *temp;
    std::string channelName, topic;
    try {
        channelName = buffer.substr(0, buffer.find(" "));
        if (channelName.empty()) throw ERR_NEEDMOREPARAMS;
        if (channelName.size() == buffer.size())
            topic = "";
        else
            topic = buffer.substr(buffer.find(" ") + 1, buffer.size() - 1);
        temp = this->findChannel(channelName);
        if (!temp) throw ERR_NOSUCHCHANNEL;
        if (!temp->isClient(client)) throw ERR_NOTONCHANNEL;
        if (topic.empty()) {
            if (temp->getTopic().empty())
                throw RPL_NOTOPIC;
            else
                throw RPL_TOPIC;
        } else {
            if (temp->getOpTopicOnly() && !temp->isOperator(client)) throw ERR_CHANOPRIVSNEEDED;
            topic.erase(topic.begin());
            temp->setTopic(topic);
            throw SUCCESS;
        }
    } catch (NUM code) {
        if (code == SUCCESS) {
            std::string response = rpl_Successful(client, *temp);
            temp->updateClients(client, response);  // TODO: Test
            client.setResponse(client.getResponse() + response);
        } else if (code == RPL_NOTOPIC)
            client.setResponse(client.getResponse() + rpl_NoTopic(*this, client, *temp));
        else if (code == RPL_TOPIC)
            client.setResponse(client.getResponse() + rpl_Topic(*this, client, *temp));
        else if (code == ERR_NOSUCHCHANNEL)
            err(ERR_NOSUCHCHANNEL, this->getHostname(), client, channelName);
        else if (code == ERR_NOTONCHANNEL)
            err(ERR_NOTONCHANNEL, this->getHostname(), client, temp->getName());
        else if (code == ERR_NEEDMOREPARAMS)
            err(ERR_NEEDMOREPARAMS, this->getHostname(), client, "TOPIC");
        else if (code == ERR_CHANOPRIVSNEEDED)
            err(ERR_CHANOPRIVSNEEDED, this->getHostname(), client, temp->getName());
    }
}
