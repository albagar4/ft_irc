#include <Client.hpp>
#include <Server.hpp>
#include <ircserv.hpp>
#include <Channel.hpp>

// Comando BOT: BOT <mode>
void Server::parseBot(std::string buffer, Client &client){
    std::string mode[3] = { "HELP", "PLAY", "TIP"};

    ft_print("Inside Bot: ");
    ft_print(buffer);
    try {
        if (buffer.empty()) throw 1;
        if (buffer.find(' ') != buffer.npos) throw 2;
        for (int i = 0; i < 3; i++) if (buffer == mode[i]) break ;
        switch (i){
            case 0:
                    //funcion de help
            case 1:
                    //funcion de play
            case 2:
                    //funcion de tip
            default:
                    //mensaje de no existe el modo
        }
    } catch (int code) {
        if (code == 1)
            client.setResponse(": bot-as!GatoConBot-as@localhost PRIVMSG " + client.getNickname() + " :Not enough parameters\r\n");
        if (code == 2)
            client.setResponse(": bot-as!GatoConBot-as@localhost PRIVMSG " + client.getNickname() + " :Extra parameters\r\n");
        std::cout << client.getResponse() << std::endl;
    }
}