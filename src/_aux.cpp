#include <Client.hpp>
#include <Server.hpp>
#include <ircserv.hpp>
void ft_print(std::string str) { std::cout << str << std::endl; }
void ft_print(std::string str, const char* color) {
    std::cout << color;
    std::cout << str << std::endl;
    std::cout << RESET;
}
void print_err(std::string errorMessage) {
    std::cout << RED;
    std::cerr << errorMessage << std::endl;
    std::cout << RESET;
    exit(1);
}
void printHelp() {
    std::cout << GREEN;
    std::cout << "The avaliable commands are:\n";
    std::cout << "\tCAP\n";
    std::cout << "\tPASS\n";
    std::cout << "\tNICK\n";
    std::cout << "\tUSER\n";
    std::cout << "\tJOIN\n";
    std::cout << "\tPART\n";
    std::cout << "\tKICK\n";
    std::cout << "\tINVITE\n";
    std::cout << "\tTOPIC\n";
    std::cout << "\tMODE\n";
    std::cout << "\tPRIVMSG\n";
    std::cout << "\tQUIT\n";
    std::cout << RESET;
}
void printConnected(Client client) {
    std::cout << BLUE;
    std::cout << "Client " << client.getHost()->h_name << " connected in socket " << client.getFd()
              << "\n";
    std::cout << RESET;
}
void printDisconnected(Client client) {
    std::cout << YELLOW;
    std::cout << "Client " << client.getHost()->h_name << " was disconnected from socket "
              << client.getFd() << "\n";
    std::cout << RESET;
}
void printCloseServer() {
    std::cout << MAGENTA;
    std::cout << "Server was closed\n";
    std::cout << RESET;
}
void printLaunchServer(const Server& server) {
    std::cout << MAGENTA;
    std::cout << ASCII_ART;
    std::cout << "Password: \t" << server.getPassword();
    std::cout << "\nPort: \t\t" << server.getPort();
    std::cout << "\nSocket: \t" << server.getServerSocket();
    std::cout << "\nHostname: \t" << server.getHostname();
    std::cout << RESET << std::endl;
}

std::vector<std::string> split(std::string input, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        if (!token.empty() && token[0] == ':') {
            tokens.push_back(token.substr(1));
            break;
        }
        tokens.push_back(token);
    }
    return tokens;
}
std::string fixSpaces(std::string buffer) {
    std::string params;
    size_t space = buffer.find(" ");
    if (space != std::string::npos) {
        size_t startOfParams = buffer.find_first_not_of(" ", space + 1);
        if (startOfParams != std::string::npos)
            params = buffer.substr(startOfParams);
        else
            params = "";
    } else
        params = "";
    return params;
}

std::map<NUM, std::string> errorMessages;
void initializeErrorMessages() {
    errorMessages[ERR_UNKNOWNERROR] = "Could not process multiple invalid parameters";
    errorMessages[ERR_NOSUCHNICK] = "No such nick/channel";
    errorMessages[ERR_NOSUCHSERVER] = "No such server";
    errorMessages[ERR_NOSUCHCHANNEL] = "No such channel";
    errorMessages[ERR_CANNOTSENDTOCHAN] = "Cannot send to channel";
    errorMessages[ERR_TOOMANYCHANNELS] = "You have joined too many channels";
    errorMessages[ERR_WASNOSUCHNICK] = "There was no such nickname";
    errorMessages[ERR_TOOMANYTARGETS] = "Duplicate recipients. No message delivered";
    errorMessages[ERR_NOORIGIN] = "No origin specified";
    errorMessages[ERR_NORECIPIENT] = "No recipient given (<command>)";
    errorMessages[ERR_NOTEXTTOSEND] = "No text to send";
    errorMessages[ERR_NOTOPLEVEL] = "No toplevel domain specified";
    errorMessages[ERR_WILDTOPLEVEL] = "Wildcard in toplevel domain";
    errorMessages[ERR_BADMASK] = "Bad Server/host mask";

    errorMessages[ERR_UNKNOWNCOMMAND] = "Unknown command";
    errorMessages[ERR_NOMOTD] = "MOTD File is missing";
    errorMessages[ERR_NOADMININFO] = "No administrative info available";
    errorMessages[ERR_FILEERROR] = "File error";

    errorMessages[ERR_NONICKNAMEGIVEN] = "No nickname given";
    errorMessages[ERR_ERRONEUSNICKNAME] = "Erroneous nickname";
    errorMessages[ERR_NICKNAMEINUSE] = "Nickname is already in use";
    errorMessages[ERR_NICKCOLLISION] = "Nickname collision KILL";
    errorMessages[ERR_UNAVAILRESOURCE] = "Nick/channel is temporarily unavailable";

    errorMessages[ERR_USERNOTINCHANNEL] = "They aren't on that channel";
    errorMessages[ERR_NOTONCHANNEL] = "You're not on that channel";
    errorMessages[ERR_USERONCHANNEL] = "is already on channel";
    errorMessages[ERR_NOLOGIN] = "User not logged in";
    errorMessages[ERR_SUMMONDISABLED] = "SUMMON has been disabled";
    errorMessages[ERR_USERSDISABLED] = "USERS has been disabled";

    errorMessages[ERR_NOTREGISTERED] = "You have not registered";
    errorMessages[ERR_NEEDMOREPARAMS] = "Not enough parameters";
    errorMessages[ERR_ALREADYREGISTERED] = "You may not reregister";
    errorMessages[ERR_PASSWDMISMATCH] = "Password incorrect";
    errorMessages[ERR_YOUREBANNEDCREEP] = "You are banned from this server";
    errorMessages[ERR_YOUWILLBEBANNED] = "You will be banned";
    errorMessages[ERR_KEYSET] = "Channel key already set";
    errorMessages[ERR_CHANNELISFULL] = "Cannot join channel (+l)";
    errorMessages[ERR_UNKNOWNMODE] = "Unknown mode character";
    errorMessages[ERR_INVITEONLYCHAN] = "Cannot join channel (+i)";
    errorMessages[ERR_BANNEDFROMCHAN] = "Cannot join channel (+b)";
    errorMessages[ERR_BADCHANNELKEY] = "Cannot join channel (+k)";
    errorMessages[ERR_BADCHANMASK] = "Bad Channel Mask";
    errorMessages[ERR_NOCHANMODES] = "Channel doesn't support modes";
    errorMessages[ERR_BANLISTFULL] = "Ban list is full";

    errorMessages[ERR_NOPRIVILEGES] = "Permission Denied- You're not an IRC operator";
    errorMessages[ERR_CHANOPRIVSNEEDED] = "You're not channel operator";
    errorMessages[ERR_CANTKILLSERVER] = "You can't kill a server!";
    errorMessages[ERR_RESTRICTED] = "Your connection is restricted!";
    errorMessages[ERR_UNIQOPRIVSNEEDED] = "You're not the original channel operator";
    errorMessages[ERR_NOOPERHOST] = "No O-lines for your host";

    errorMessages[ERR_UMODEUNKNOWNFLAG] = "Unknown MODE flag";
    errorMessages[ERR_USERSDONTMATCH] = "Cannot change mode for other users";

    // Additional error codes
    errorMessages[ERR_HELPNOTFOUND] = "Help not found";
    errorMessages[ERR_INVALIDCAPCMD] = "Invalid CAP command";
    errorMessages[ERR_NICKLOCKED] = "You must use a registered nick to perform this command";
    errorMessages[ERR_SASLFAIL] = "SASL authentication failed";
    errorMessages[ERR_SASLTOOLONG] = "SASL message too long";
    errorMessages[ERR_SASLABORTED] = "SASL authentication aborted";
    errorMessages[ERR_SASLALREADY] = "You have already authenticated using SASL";

    errorMessages[ERR_UNKNOWN] = "Unknown error";
}

void err(NUM code, std::string hostname, Client& client, std::string target) {
    std::ostringstream ss;
    ss << code;
    std::string response = ":" + hostname + " " + ss.str() + " " + client.getNick();
    if (!target.empty()) response += " " + target;
    response += " :" + errorMessages[code] + "\r\n";

    client.setResponse(client.getResponse() + response);
}
