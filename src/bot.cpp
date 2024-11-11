#include <Client.hpp>
#include <Server.hpp>
#include <ircserv.hpp>
#include <Channel.hpp>

static void botPlay(Client &client){
    std::string message = ":bot-as!GatoConBot-as@localhost PRIVMSG " + client.getNickname() + " :Welcome to Russian Roulette!\n";
    int player;
    int bot;
    
    srand(time(NULL));
    for (int i = 6; i > 0; i++){
        message += "You have a 1 in " + i + " chance of dying. Let's spin the gun chamber...\n";
        player = rand() % i + 1;
        bot = rand() % i + 1;
        if (player == 1) message += client.getNick() + " pulled the trigger and... *BANG*! You're dead! XP\n";
        else message += client.getNick() + " pulled the trigger and... *click*! You're safe... for now.\n";
        if (bot == 1) message += "bot-as pulled the trigger and... *BANG*! bot-as is dead! XP\n";
        else message += "bot-as pulled the trigger and... *click*! He's safe... for now.\n";
        if (bot == 0 && player == 0) message += "Both of you are safe. Let's play again until the bullets run out or one of you dies! :)\n";
        if (bot == 1 || player == 1) break ;
    }
    if (bot == 1 && player != 1) message += client.getNick() + " wins! Congratulations! :)\n\r";
    else if (bot != 1 && player == 1) message += "bot-as wins! Better luck next time! :)\n\r";
    else if (bot != 1 && player != 1) message += "Both survived! Aw ! That's not fun... :(\n\r";
    else if (bot == 1 && player == 1) message += "Both of you died! That's a tie! :)\n\r";
    client.setResponse(message);
}

static void botTip(Client &client){
    std::string message = ":bot-as!GatoConBot-as@localhost PRIVMSG " + client.getNickname() + " :Tip of the day- ";
    int random;

    srand(time(NULL));
    random = rand() % 10 + 1;
    switch (random){
        case 1:
            message += "They say you can be anything you want. So why this?!\r\n"; break ;
        case 2:
            message += "A balanced diet means a cookie in each hand.\r\n"; break ;
        case 3:
            message += "When life closes a door, just open it again. It’s a door. That’s how they work.\r\n"; break ;
        case 4:
            message += "If you’re struggling to be productive, just sit and stare at the screen. You’ll look busy enough.\r\n" break ;
        case 5:
            message += "If you’re waiting for a sign, this isn’t it. Maybe try again tomorrow?\r\n"; break ;
        case 6:
            message += "Remember, it’s never too late to give up on your dreams and take a nap instead.\r\n"; break ;
        case 7:
            message += "You’re the reason ‘Ctrl+Z’ was invented."; break ;
        case 8:
            message += "Think positive! You tried your best… and it still wasn’t great, but hey, points for effort!\r\n"; break ;
        case 9:
            message += "Remember, every great idea starts with ‘This might be stupid, but…\r\n"; break ;
        case 10:
            message += "When life gives you lemons, just throw them at someone. It’s way more satisfying.\r\n"; break ;
    }
    client.setResponse(message);
}

// PRIVMSG "bot-as :<mode>"
void Server::parseBot(std::string buffer, Client &client){
    std::string mode[3] = { ":HELP", ":PLAY", ":TIP"};

    ft_print("Inside Bot: ");
    ft_print(buffer);
    try {
        if (buffer.find(' ') != buffer.npos) throw 1;
        buffer = buffer.toUpper();
        for (int i = 0; i < 3; i++) if (buffer == mode[i]) break ;
        switch (i){
            case 0:
                    client.setResponse(":bot-as!GatoConBot-as@localhost PRIVMSG " + client.getNickname() + " :Ask me 'PLAY' or 'TIP'\r\n"); break ;
            case 1:
                    botPlay(client); break ;
            case 2:
                    botTip(client); break ;
            default:
                    client.setReponse(":bot-as!GatoConBot-as@localhost PRIVMSG " + client.getNickname() + " :Invalid command. Ask me 'HELP' for more info\r\n");
        }
    } catch (int code) {
        if (code == 1)
            client.setResponse(":bot-as!GatoConBot-as@localhost PRIVMSG " + client.getNickname() + " :Extra parameters\r\n");
    }
    std::cout << client.getResponse() << std::endl;
}