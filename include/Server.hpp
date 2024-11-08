#ifndef SERVER_HPP
#define SERVER_HPP

#define ASCII_ART                                 \
    "   __   _              _               \n"   \
    "  / _| | |            (_)              \n"   \
    " | |_  | |_            _   _ __    ___ \n"   \
    " |  _| | __|          | | | '__|  / __|\n"   \
    " | |   | |_           | | | |    | (__ \n"   \
    " |_|    \\__|          |_| |_|     \\___|\n" \
    "              ______                   \n"   \
    "             |______|                  \n"
#include <Channel.hpp>
#include <Client.hpp>
#include <ircserv.hpp>

enum NUM {
    ERR_NEEDMOREPARAMS = 461,
    ERR_ALREADYREGISTERED = 462,
    ERR_PASSWDMISMATCH = 464,
    ERR_NOTREGISTERED = 451,
    ERR_UNKNOWNCOMMAND = 421,
};

extern std::map<NUM, std::string> errorMessages;

class Server {
   private:
    typedef void (Server::*authFunctions)(std::string, Client &);
    typedef void (Server::*cmdFunctions)(std::string, Client &);
    authFunctions authentification[4];
    cmdFunctions commands[8];

    Server() {};
    void createServerSocket(void);
    std::string password;
    int port;
    int serverSocket;
    std::string hostname;
    sockaddr_in serverAddress;
    std::vector<struct pollfd> fds;
    std::map<int, Client> map;
    std::vector<Channel> channels;

   public:
    Server(std::string port, std::string password);
    ~Server();

    // Getters
    int getServerSocket(void) const;
    std::string getPassword() const;
    int getPort() const;
    std::string getHostname() const;
    std::map<int, Client> getMap(void) const;

    void printChannels();
    // Setters
    void setAuthFunctions(void);
    void setCmdFunctions(void);
    void addChannel(Channel channel);

    int checkConnections(void);
    int iterateFds(void);
    void newConnection();
    void manageUpdates(Client &client);
    void parseCommands(char *buffer, Client &client);
    void disconnectClient(Client &client);
    bool isNewChannel(std::string name);
    Channel *findChannel(std::string name);
    void closeChannel(Channel channel);
    // Commands
    void parseCap(std::string buffer, Client &client);
    void parsePass(std::string buffer, Client &client);
    void parseNick(std::string buffer, Client &client);
    void parseUser(std::string buffer, Client &client);
    void parseJoin(std::string buffer, Client &client);
    void parsePart(std::string buffer, Client &client);
    void parseKick(std::string buffer, Client &client);
    void parseInvite(std::string buffer, Client &client);
    void parseTopic(std::string buffer, Client &client);
    void parseMode(std::string buffer, Client &client);
    void parsePrivMsg(std::string buffer, Client &client);
    void parseQuit(std::string buffer, Client &client);
};

void initializeErrorMessages();

std::ostream &operator<<(std::ostream &os, const Server &server);
#endif
