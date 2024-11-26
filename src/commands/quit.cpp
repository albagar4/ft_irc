#include <Client.hpp>
#include <Server.hpp>
#include <ircserv.hpp>

void Server::parseQuit(std::string buffer, Client &client) {
    std::string response = ":" + client.getHostname() + " QUIT :" + buffer + "\r\n";
    std::vector<Channel *> userChannels = this->findUserChannels(client);
    std::vector<Channel *>::iterator it = userChannels.begin();
    for (; it != userChannels.end(); it++) {
        Channel *channel = *it;
        channel->updateClients(client, response);
    }
    client.setResponse("ERROR :Closing link: [" + client.getHostname() + "] (Quit: " + buffer +
                       ")\r\n");
    this->disconnectClient(client);
}
