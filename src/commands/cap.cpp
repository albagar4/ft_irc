#include <Client.hpp>
#include <Server.hpp>
#include <ircserv.hpp>

void Server::parseCap(std::string buffer, Client &client) {
    if (buffer == "LS" || buffer == "LS 302")
        client.setResponse("CAP * LS\r\n");
    else {
        std::ostringstream oss;
        oss << ERR_UNKNOWNERROR;

        std::string message = errorMessages[ERR_UNKNOWNERROR];
        std::string response = oss.str() + " " + client.getHostname() + "CAP{ " + buffer + "} :" + message + "\r\n";
        client.setResponse(response);
    }
}
