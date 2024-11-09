#include <Client.hpp>
#include <Server.hpp>
#include <ircserv.hpp>

static std::string err_NeedMoreParams(Server server, Client client) {
    std::string response = ":" + server.getHostname() + " 461 ";
    response += client.getNick();
    response += " TOPIC :Not enough parameters";
    response += "\r\n";
    return response;
}
static std::string err_NoSuchChannel(Server server, Client client, std::string channel) {
    std::string response = ":" + server.getHostname() + " 403 ";
    response += client.getNick();
    response += " ";
    response += channel;
    response += " :No such channel";
    response += "\r\n";
    return response;
}
static std::string err_NotOnChannel(Server server, Client client, Channel channel) {
    std::string response = ":" + server.getHostname() + " 442 ";
    response += client.getNick();
    response += " ";
    response += channel.getName();
    response += " :You're not on that channel";
    response += "\r\n";
    return response;
}

static std::string err_ChanOpPrivsNeeded(Server server, Client client, Channel channel) {
    std::string response = ":" + server.getHostname() + " 482 ";
    response += client.getNick();
    response += " ";
    response += channel.getName();
    response += " :You're not channel operator";
    response += "\r\n";
    return response;
}

static std::string rpl_NoTopic(Server server, Client client, Channel channel) {
    std::string response = ":" + server.getHostname() + " 331 ";
    response += client.getNick();
    response += " ";
    response += channel.getName();
    response += " :No topic is set";
    response += "\r\n";
    return response;
}

static std::string rpl_Topic(Server server, Client client, Channel channel) {
    std::string response = ":" + server.getHostname() + " 332 ";
    response += client.getNick();
    response += " ";
    response += channel.getName();
    response += " :" + channel.getTopic();
    response += "\r\n";
    return response;
}

static std::string rpl_Successful(Client client, Channel channel) {
    std::string response = ":" + client.getHostname();
    response += " TOPIC : ";
    response += channel.getName();
    response += " :" + channel.getTopic();
    response += "\r\n";
    return response;
}

// static std::string errorReply() {
//   errorMessages[]
// }

void Server::parseTopic(std::string buffer, Client &client) {
    Channel *temp;
    std::string channelName, topic;
    try {
        channelName = buffer.substr(0, buffer.find(" "));
        if (channelName.empty()) throw 461;
        if (channelName.size() == buffer.size())
            topic = "";
        else
            topic = buffer.substr(buffer.find(" ") + 2, buffer.size() - 1);
        temp = this->findChannel(channelName);
        if (!temp) throw 403;
        if (!temp->isClient(client)) throw 442;
        if (topic.empty()) {
            if (temp->getTopic().empty())
                throw 331;
            else
                throw 332;
        } else {
            if (!temp->isOperator(client)) throw 482;
            temp->setTopic(topic);
            throw 0;
        }
    } catch (int code) {
        if (code == 0)
            client.setResponse(rpl_Successful(client, *temp));
        else if (code == 331)
            client.setResponse(rpl_NoTopic(*this, client, *temp));
        else if (code == 332)
            client.setResponse(rpl_Topic(*this, client, *temp));
        else if (code == 403)
            client.setResponse(err_NoSuchChannel(*this, client, channelName));
        else if (code == 442)
            client.setResponse(err_NotOnChannel(*this, client, *temp));
        else if (code == 461)
            client.setResponse(err_NeedMoreParams(*this, client));
        else if (code == 482)
            client.setResponse(err_ChanOpPrivsNeeded(*this, client, *temp));
    }
}
