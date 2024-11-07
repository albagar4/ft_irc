#include <Client.hpp>
#include <Server.hpp>
#include <ircserv.hpp>
void Server::parsePart(std::string buffer, Client &client) {
    (void)client;
    ft_print("Inside Part: ");
    ft_print(buffer);
}
