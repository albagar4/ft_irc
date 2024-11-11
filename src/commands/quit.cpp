#include <Client.hpp>
#include <Server.hpp>
#include <ircserv.hpp>

void Server::parseQuit(std::string buffer, Client &client) {
    std::string reason = buffer;
    this->disconnectClient(client);
}
