#include <Client.hpp>
#include <Server.hpp>
#include <ircserv.hpp>
void Server::parseMode(std::string buffer, Client &client) {
    (void)client;
    ft_print("Inside Mode: ");
    ft_print(buffer);
}
