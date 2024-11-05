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
#include <Client.hpp>
#include <ircserv.hpp>

enum {
    
};

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
    sockaddr_in serverAddress;
    std::vector<struct pollfd> fds;
    std::map<int, Client> map;

   public:
    Server(std::string port, std::string password);
    ~Server();

    // Getters
    int getServerSocket(void) const;
    std::string getPassword() const;
    int getPort() const;
    std::map<int, Client> getMap(void) const;

    // Setters
    void setAuthFunctions(void);
    void setCmdFunctions(void);

    int checkConnections(void);
    int iterateFds(void);
    void newConnection();
    void manageUpdates(Client &client);
    void parseCommands(char *buffer, Client &client);

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

std::ostream &operator<<(std::ostream &os, const Server &server);
#endif
