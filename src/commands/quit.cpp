#include <Client.hpp>
#include <Server.hpp>
#include <ircserv.hpp>

void Server::parseQuit(std::string buffer, Client &client) {
    (void)client;
    ft_print("Inside Quit: ");
    ft_print(buffer);
}
