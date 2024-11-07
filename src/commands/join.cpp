#include <Client.hpp>
#include <Server.hpp>
#include <ircserv.hpp>

static std::string rpl_NamReply(Server server, Client client, Channel channel) {
    std::string response = server.getHostname() + " 353 ";
    response += client.getNick() + " ";
    response += "= ";
    response += channel.getName() + " :";
    response += channel.getUserList();
    return response;
}
static std::string rpl_EndOfNames(Server server, Client client, Channel channel) {
    std::string response = server.getHostname() + " 366 ";
    response += client.getNick() + " ";
    response += channel.getName() + " :";
    response += "End of /NAMES list.";
    return response;
}
static std::string rpl_Topic(Server server, Client client, Channel channel) {
    std::string response = server.getHostname() + " 332 ";
    response += client.getNick() + " ";
    response += channel.getName() + " :";
    response += channel.getTopic();
    return response;
}
static std::string rpl_Successful(Server server, Client client, Channel channel) {
    std::string response = client.getHostname();
    response += " JOIN : ";
    response += channel.getName();
    if (channel.getTopic() != "") response += "\r\n" + rpl_Topic(server, client, channel);
    response += "\r\n" + rpl_NamReply(server, client, channel);
    response += "\r\n" + rpl_EndOfNames(server, client, channel) + "\r\n";
    return response;
}
static std::string err_NeedMoreParams(Server server, Client client) {
    std::string response = server.getHostname() + " 461 ";
    response += client.getNick();
    response += " JOIN :Not enough parameters";
    return response;
}
static std::string err_ChannelIsFull(Server server, Client client, Channel channel) {
    std::string response = server.getHostname() + " 471 ";
    response += client.getNick() + " ";
    response += channel.getName();
    response += " :Cannot join channel (+l)";
    return response;
}
// static std::string err_InviteOnlyChan(Server server, Client client, Channel channel) {
//     std::string response = server.getHostname() + " 473 ";
//     response += client.getNick() + " ";
//     response += channel.getName();
//     response += " :Cannot join channel (+i)";
//     return response;
// }
void Server::parseJoin(std::string buffer, Client &client) {
    Channel *temp;
    client.setNick("alvega-g");
    client.setUser("alvega-g");
    client.setHostname();
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
                this->findChannel(tokens[i])->addClient(client);
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
    std::cout << client.getResponse() << std::endl;
    printChannels();
}
