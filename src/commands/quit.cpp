#include <Client.hpp>
#include <Server.hpp>
#include <ircserv.hpp>

void Server::parseQuit(std::string buffer, Client &client) {
    std::string response = ":" + client.getHostname() + " QUIT :" + buffer + "\r\n";
    std::vector<Channel> userChannels = this->findUserChannels(client);
    // if (userChannels.empty()) print_err("PANIC");
    std::vector<Channel>::iterator it = userChannels.begin();
    for (; it != userChannels.end(); it++) {
        it->updateClients(client, response);
    }
    client.setResponse(
        "ERROR :Closing link: [" + client.getHostname() + "] (Quit: " + buffer +
        ")\r\n");  //         TODO: Test, also test server.findUserChannels to see if it works
    //   this->sendResponse(); // This is probably needed, since the user gets disconnected right
    //                           below and would never recieve the message
    this->disconnectClient(client);
}
