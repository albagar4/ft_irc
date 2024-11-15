#include <Client.hpp>
#include <Server.hpp>
#include <ircserv.hpp>

void Server::parseNick(std::string buffer, Client &client) {
    try {
        if (client.getPass() == false) throw 451;
        if (buffer.empty()) throw 431;
        if (buffer.find('#') != buffer.npos || buffer.find(':') != buffer.npos || buffer.find(' ') != buffer.npos || isdigit(buffer[0])) throw 432;
        for (unsigned long i = 0; i < this->getMap().size(); i++)
        {
            // ft_print(this->map[i].getNick());
            if (this->map[i].getNick().compare(buffer) == 0) throw 433;
        }
        client.setNick(buffer);
    } catch (int code) {
        if (code == 451)
            client.setResponse(":" + this->getHostname() + " 451 :You have not registered\r\n Password hasn't been validated\r\n");
        if (code == 431)
            client.setResponse(":" + this->getHostname() + " 431 :No nickname given\r\n");
        if (code == 432)
            client.setResponse(":" + this->getHostname() + " 432 " + buffer + " :Erroneus nickname\r\n");
        if (code == 433)
            client.setResponse(":" + this->getHostname() + " 433 " + buffer + " :Nickname is already in use\r\n");
        std::cout << client.getResponse() << std::endl;
    }
}
