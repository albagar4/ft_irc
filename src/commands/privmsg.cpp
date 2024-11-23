#include <Client.hpp>
#include <Server.hpp>
#include <ircserv.hpp>

void Server::parsePrivMsg(std::string buffer, Client &client) {
    std::string target, message;
    Client *aux;
    bool find = false;

    try {
        if (buffer.empty()) throw 461;
        if (buffer[0] == ':') throw 411;
        target = buffer.substr(0, buffer.find(":") - 1);
        if (target.find(" ") != target.npos) throw 407;
        if (buffer.find(":") == buffer.npos) throw 412;
        message = buffer.substr(buffer.find(":"), buffer.size() - 1);
        if (message.empty()) throw 412;
        if (target[0] == '#') {
            Channel *temp = this->findChannel(target);
            if (!temp) throw 403;
            for (unsigned long i = 0; i < temp->getClients().size(); i++) {
                if (temp->getClients()[i].getNick().compare(client.getNick()) == 0) {
                    find = true;
                    break;
                }
            }
            if (find == false) throw 404;
            client.setResponse(":" + client.getHostname() + " PRIVMSG " + target + " " + message +
                               "\r\n");
            temp->updateClients(client, client.getResponse());
        } else {
            if (target == "bot-as")
                this->parseBot(message, client);
            else {
                aux = this->findClient(target);
                if (!aux) throw 401;
                if (message.substr(1, 3).compare("DCC") == 0)
                    parseFileTransfer(message, client, *aux);
                else {
                    aux->setResponse(":" + client.getHostname() + " PRIVMSG " + target + " " +
                                     message + "\r\n");
                }
            }
        }
    } catch (int code) {
        if (code == 461)
            client.setResponse(":" + this->getHostname() +
                               " 461 PRIVMSG :Not enough parameters\r\n");
        if (code == 407)
            client.setResponse(":" + this->getHostname() + " 407 " + client.getNick() + " " +
                               target + ":Duplicate recipients. No message delivered\r\n");
        if (code == 411)
            client.setResponse(":" + this->getHostname() + " 411 " + client.getNick() +
                               " :No recipient given\r\n");
        if (code == 412)
            client.setResponse(":" + this->getHostname() + " 412 " + client.getNick() +
                               " :No text given\r\n");
        if (code == 403)
            client.setResponse(":" + this->getHostname() + " 403 " + client.getNick() + " " +
                               target + " :No such channel\r\n");
        if (code == 401)
            client.setResponse(":" + this->getHostname() + " 401 " + client.getNick() + " " +
                               target + " :No such nick/channel\r\n");
        if (code == 404)
            client.setResponse(":" + this->getHostname() + " 404 " + client.getNick() + " " +
                               target + " :Cannot send to channel\r\n");
    }
}
