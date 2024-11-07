#include <Client.hpp>
#include <Server.hpp>
#include <ircserv.hpp>

void Server::parseJoin(std::string buffer, Client &client) {
    std::vector<std::string> tokens = split(buffer, ',');
    for (size_t i = 0; i < tokens.size(); i++) {
        if (tokens.size() > 1 && tokens[i].find_first_of(":") != std::string::npos) {
            ft_print(
                "Joining multiple channels and setting topic in the same command is not supported",
                RED);
            return;
        }
        std::string topic = tokens[i].substr(tokens[i].find_first_of(":") + 1, tokens[i].size());
        if (topic != tokens[i]) {
            tokens[i] = tokens[i].substr(0, tokens[i].find_first_of(":") - 1);
        } else {
            topic = "";
        }
        if (isNewChannel(tokens[i]) == true) {
            Channel newChannel(tokens[i], topic);
            newChannel.addClient(client);
            this->channels.push_back(newChannel);
        } else {
            this->findChannel(tokens[i])->addClient(client);
        }
    }

    printChannels();
}
