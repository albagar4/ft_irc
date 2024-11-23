#include <Client.hpp>
#include <Server.hpp>
#include <ircserv.hpp>

void Server::parseCap(std::string buffer, Client &client) {
    if (buffer == "LS" || buffer == "LS 302")
        client.setResponse("CAP * LS\r\n");
    else
        err(ERR_UNKNOWNERROR, this->getHostname(), client, "CAP{ " + buffer + "} :Command CAP must be followed by LS or LS 302");
}
