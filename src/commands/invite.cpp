#include <Client.hpp>
#include <Server.hpp>
#include <ircserv.hpp>
void Server::parseInvite(std::string buffer, Client &client) {
    (void)client;
    ft_print("Inside Invite: ");
    ft_print(buffer);
}
