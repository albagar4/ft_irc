#include <Client.hpp>
#include <Server.hpp>
#include <ircserv.hpp>

void Server::parseUser(std::string buffer, Client &client) {
    (void)client;
    ft_print("Inside User: ");
    ft_print(buffer);
}
