#include <Client.hpp>
#include <Server.hpp>
#include <ircserv.hpp>

void Server::parseNick(std::string buffer, Client &client) {
    try {
        if (client.getPass() == false) throw 451;
        if (buffer.empty()) throw 431;
        if (buffer.find('#') != buffer.npos || buffer.find(':') != buffer.npos || buffer.find(' ') != buffer.npos || isdigit(buffer[0])) throw 432;
        for (unsigned long i = 0; i < this->getMap().size(); i++)
            if (this->map[i].getNick().compare(buffer) == 0) throw 433;
        if (!client.getNick().empty()) {
            std::vector<Channel> channel_list = this->findUserChannels(client);
            std::string message = ":" + client.getHostname() + " NICK :" + buffer + "\r\n";

            for (size_t i = 0; i < channel_list.size(); i++)
                channel_list[i].updateClients(client, message);
            client.setResponse(message);
        }
        client.setNick(buffer);
    } catch (int code) {
        if (code == 451)
            err(ERR_NOTREGISTERED, this->getHostname(), client);
        if (code == 431)
            err(ERR_NONICKNAMEGIVEN, this->getHostname(), client);
        if (code == 432)
            err(ERR_ERRONEUSNICKNAME, this->getHostname(), client, buffer);
        if (code == 433)
            err(ERR_NICKNAMEINUSE, this->getHostname(), client, buffer);
    }
}
