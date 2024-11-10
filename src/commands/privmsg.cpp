#include <Client.hpp>
#include <Server.hpp>
#include <ircserv.hpp>

// Falta el error 404 ERR_CANNOTSENDTOCHAN, ERR_NOTOPLEVEL (413), ERR_WILDTOPLEVEL (414), RPL_AWAY (301)

void Server::parsePrivMsg(std::string buffer, Client &client) {
    std::vector<std::string> tokens = split(buffer, ',');
    std::string target, message;
    bool target = false;

    ft_print("Inside PrivMsg: ");
    ft_print(buffer);
    try {
        if (buffer.empty()) throw 461;
        if (tokens.size() > 2) throw 407;
        if (tokens.size() < 2){
            if (buffer.find(':') != buffer.npos) throw 411;
            else throw 412;
        }
        for (i = 0; i < tokens.size(); i++) {
            target = tokens[i].substr(0, tokens[i].find(" "));
            message = tokens[i].substr(tokens[i].find(" ") + 1, tokens[i].size() - 1);
            if (target[0] == '#'){
                Channel *temp = this->findChannel(target);
                if (!temp) throw 403;
            }
            else{
                if (target == "bot-as") this->parseBot(message, client);
                else {
                    for (unsigned long i = 0; i < this->getMap().size(); i++)
                    {
                        if (this->map[i].getNick().compare(target) == 0){
                            target = true;
                            Client aux = this->map[i].getNick();
                            break ;
                        }
                    }
                    if (target == false) throw 401;
                }
            }
        }
    } catch (int code) {
        if (code == 461)
            client.setResponse(":" + this->getHostname() + " 461 " + client.getNick() + " PRIVMSG :No such nick/channel\r\n");
        if (code == 407)
            client.setResponse(":" + this->getHostname() + " 407 " + client.getNick() + buffer.substr(0, find(':')) + ":Duplicate recipients. No message delivered\r\n"); //ESTE TENGO QUE REPASARLO BIEN
        if (code == 411)
            client.setResponse(":" + this->getHostname() + "411" + client.getNick() + " :No recipient given");
        if (code == 412)
            client.setResponse(":" + this->getHostname() + "412" + client.getNick() + " :No text given");
        if (code == 403)
            client.setResponse(":" + this->getHostname() + "403" + client.getNick() + " " + target + " :No such channel\r\n");
        if (code == 401)
            client.setResponse(":" + this->getHostname() + " 401 " + client.getNick() + " " + target + " :No such nick/channel\r\n");
        std::cout << client.getResponse() << std::endl;
    }
}
