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
    response += client.getNick();
    response += channel.getName() + " :";
    response += "End of /NAMES list.";
    return response;
}
static std::string rpl_Topic(Server server, Client client, Channel channel) {
    std::string response = server.getHostname() + " 332 ";
    response += client.getNick();
    response += channel.getName() + " :";
    response += channel.getTopic();
    return response;
}
static void rpl_Successful(Server server, Client client, Channel channel) {
    std::string response = client.getHostname();
    response += " JOIN : ";
    response += channel.getName();

    if (channel.getTopic() != "") response += "\n" + rpl_Topic(server, client, channel);
    response += "\n" + rpl_NamReply(server, client, channel);
    response += "\n" + rpl_EndOfNames(server, client, channel);
    std::cout << "Reply would be:\n" << response << std::endl;
}

static std::string err_NeedMoreParams(Server server, Client client) { ; }
static std::string err_ChannelIsFull(Server server, Client client, Channel channel) { ; }

void Server::parseJoin(std::string buffer, Client &client) {
    Channel *temp;
    try {
        if (buffer.empty()) throw 461;
        std::vector<std::string> tokens = split(buffer, ',');
        for (size_t i = 0; i < tokens.size(); i++) {
            if (tokens.size() > 1 && tokens[i].find_first_of(":") != std::string::npos) {
                ft_print(
                    "Joining multiple channels and setting topic in the same command is not "
                    "supported",
                    RED);
                return;
            }
            std::string topic =
                tokens[i].substr(tokens[i].find_first_of(":") + 1, tokens[i].size());
            if (topic != tokens[i]) {
                tokens[i] = tokens[i].substr(0, tokens[i].find_first_of(":") - 1);
            } else {
                topic = "";
            }
            if (isNewChannel(tokens[i]) == true) {
                Channel newChannel(tokens[i], topic);
                newChannel.addClient(client);
                this->channels.push_back(newChannel);
            } else {
                temp = this->findChannel(tokens[i]);
                if (temp->getUserLimit() == temp->getClients().size()) throw 471;
                // Check if user is invited: if (temp->getInviteOnly() == true && ) throw 473;
                this->findChannel(tokens[i])->addClient(client);
            }
            rpl_Successful(*this, client, *this->findChannel(tokens[i]));
        }
    } catch (int code) {
        if (code == 461)
            err_NeedMoreParams(*this, client);
        else if (code == 471)
            err_ChannelIsFull(*this, client, temp);
        // else if (code == 473)
        //  err_InviteOnlyChan(*this, client, temp);
    }
    printChannels();
}
