#include <Client.hpp>
#include <Server.hpp>
#include <ircserv.hpp>
void Server::parseKick(std::string buffer, Client &client) {
    (void)client;
    ft_print("Inside Kick: ");
    ft_print(buffer);
}
