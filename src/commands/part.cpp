#include <Client.hpp>
#include <Server.hpp>
#include <ircserv.hpp>

static std::string err_NeedMoreParams(Server server, Client client) {
    std::string response = server.getHostname() + " 461 ";
    response += client.getNick();
    response += " PART :Not enough parameters";
    response += "\r\n";
    return response;
}
static std::string err_NoSuchChannel(Server server, Client client, std::string channel) {
    std::string response = server.getHostname() + " 403 ";
    response += client.getNick();
    response += " ";
    response += channel;
    response += " :No such channel";
    response += "\r\n";
    return response;
}
static std::string err_NotOnChannel(Server server, Client client, Channel channel) {
    std::string response = server.getHostname() + " 442 ";
    response += client.getNick();
    response += " ";
    response += channel.getName();
    response += " :You're not on that channel";
    response += "\r\n";
    return response;
}
static std::string rplSuccessful(Client client, Channel channel) {
    std::string response = client.getHostname();
    response += " PART : ";
    response += channel.getName();
    response += "\r\n";
    return response;
}
void Server::parsePart(std::string buffer, Client &client) {
    Channel *temp;
    size_t i;
    std::vector<std::string> tokens = split(buffer, ',');
    std::string name, reason;
    // Este trycatch está mal, debería estar dentro del for loop para tener en cuenta que te puedes
    // salir de multiples canales en un solo comando (i.e. PART #canal1,#canal2)
    // Ahora mismo solo funciona con un solo canal por comando
    try {
        if (buffer.empty()) throw 461;
        for (i = 0; tokens.size(); i++) {
            name = tokens[i].substr(0, tokens[i].find(" "));
            reason = tokens[i].substr(tokens[i].find(" ") + 1, tokens[i].size());
            temp = this->findChannel(name);
            if (!temp) throw 403;
            if (temp->isClient(client)) {
                temp->disconnectClient(client);
                if (temp->isEmpty()) this->closeChannel(*temp);
                throw 0;
            } else
                throw 442;
        }
    } catch (int code) {
        if (code == 0)
            client.setResponse(rplSuccessful(client, *temp));
        else if (code == 461)
            client.setResponse(err_NeedMoreParams(*this, client));
        else if (code == 403)
            client.setResponse(err_NoSuchChannel(*this, client, name));
        else if (code == 442)
            client.setResponse(err_NotOnChannel(*this, client, *temp));
    }
}
