#include <Client.hpp>
#include <Server.hpp>
#include <ircserv.hpp>
void Server::parseTopic(std::string buffer, Client &client) {
    (void)client;
    ft_print("Inside Topic: ");
    ft_print(buffer);
}
