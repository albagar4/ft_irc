#include <Client.hpp>
#include <Server.hpp>
#include <ircserv.hpp>

void Server::parseCap(std::string buffer, Client &client) {
    (void)client;
    ft_print("Inside Cap: ");
    ft_print(buffer);
}
