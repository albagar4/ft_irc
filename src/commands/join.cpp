#include <Client.hpp>
#include <Server.hpp>
#include <ircserv.hpp>

static std::string err_NeedMoreParams(Server server, Client client) {
    std::string response = server.getHostname() + " 461 ";
    response += client.getNick();
    response += " JOIN :Not enough parameters";
    response += "\r\n";
    return response;
}
static std::string err_ChannelIsFull(Server server, Client client, Channel channel) {
    std::string response = server.getHostname() + " 471 ";
    response += client.getNick() + " ";
    response += channel.getName();
    response += " :Cannot join channel (+l)";
    response += "\r\n";
    return response;
}
// static std::string err_InviteOnlyChan(Server server, Client client, Channel channel) {
//     std::string response = server.getHostname() + " 473 ";
//     response += client.getNick() + " ";
//     response += channel.getName();
//     response += " :Cannot join channel (+i)";
//     response += "\r\n";
//     return response;
// }
static std::string rpl_NamReply(Server server, Client client, Channel channel) {
    std::string response = server.getHostname() + " 353 ";
    response += client.getNick() + " ";
    response += "= ";
    response += channel.getName() + " :";
    response += channel.getUserList();
    response += "\r\n";
    return response;
}
static std::string rpl_EndOfNames(Server server, Client client, Channel channel) {
    std::string response = server.getHostname() + " 366 ";
    response += client.getNick() + " ";
    response += channel.getName() + " :";
    response += "End of /NAMES list.";
    response += "\r\n";
    return response;
}
static std::string rpl_Topic(Server server, Client client, Channel channel) {
    std::string response = server.getHostname() + " 332 ";
    response += client.getNick() + " ";
    response += channel.getName() + " :";
    response += channel.getTopic();
    response += "\r\n";
    return response;
}
static std::string rpl_Successful(Server server, Client client, Channel channel) {
    std::string response = client.getHostname();
    response += " JOIN : ";
    response += channel.getName();
    response += "\r\n";
    if (channel.getTopic() != "") response += rpl_Topic(server, client, channel);
    response += rpl_NamReply(server, client, channel);
    response += rpl_EndOfNames(server, client, channel);
    return response;
}
void Server::parseJoin(std::string buffer, Client &client) {
    Channel *temp;
    try {
        if (buffer.empty()) throw 461;
        std::vector<std::string> tokens = split(buffer, ',');
        for (size_t i = 0; i < tokens.size(); i++) {
            size_t colonPos = tokens[i].find_first_of(":");
            if (tokens.size() > 1 && colonPos != std::string::npos) throw 461;
            std::string topic = tokens[i].substr(colonPos + 1, tokens[i].size());
            if (topic != tokens[i]) {
                tokens[i] = tokens[i].substr(0, colonPos - 1);
            } else {
                topic = "";
            }
            if (isNewChannel(tokens[i]) == true) {
                Channel newChannel(tokens[i], topic);
                newChannel.addClient(client);
                this->channels.push_back(newChannel);
            } else {
                temp = this->findChannel(tokens[i]);
                if ((size_t)temp->getUserLimit() == temp->getClients().size()) throw 471;
                // Check if user is invited: if (temp->getInviteOnly() == true && ) throw 473;
                temp->addClient(client);
            }
            client.setResponse(rpl_Successful(*this, client, *this->findChannel(tokens[i])));
        }
    } catch (int code) {
        if (code == 461)
            client.setResponse(err_NeedMoreParams(*this, client));
        else if (code == 471)
            client.setResponse(err_ChannelIsFull(*this, client, *temp));
        // else if (code == 473)
        //  client.setResponse(err_InviteOnlyChan(*this, client, temp));
    }
}
