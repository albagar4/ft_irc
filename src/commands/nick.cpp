#include <Client.hpp>
#include <Server.hpp>
#include <ircserv.hpp>

void Server::parseNick(std::string buffer, Client &client) {
    ft_print("Inside Nick: ");
    ft_print(buffer);
    if (buffer.empty()){
        print_err(this->getHostname() + " 431 :No nickname given");
        return ;
    }
    if (buffer.find('#') >= 0 || buffer.find(':') >= 0|| buffer.find(' ') >= 0 || isdigit(buffer[0])){
        print_err(this->getHostname() + " 432 " + buffer + " :Erroneus nickname");
        return ;
    }
    for (int i = 0; i < this->getMap().size(); i++)
    {
        if (this->map[i].getNick().compare(buffer) == 0){
            print_err(this->getHostname() + " 433 " + buffer + " :Nickname is already in use");
            return ;
        }
    }
    client.setNick(buffer);
}
