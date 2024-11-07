#include <Client.hpp>
#include <Server.hpp>
#include <ircserv.hpp>

void Server::parseNick(std::string buffer, Client &client) {
    (void)client;
    ft_print("Inside Nick: ");
    ft_print(buffer);
}
