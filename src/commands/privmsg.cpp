#include <Client.hpp>
#include <Server.hpp>
#include <ircserv.hpp>
void Server::parsePrivMsg(std::string buffer, Client &client) {
    (void)client;
    ft_print("Inside PrivMsg: ");
    ft_print(buffer);
}
