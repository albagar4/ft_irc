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
#include <File.hpp>
#include <ircserv.hpp>

class Channel;
class Server {
   private:
    typedef void (Server::*authFunctions)(std::string, Client &);
    typedef void (Server::*cmdFunctions)(std::string, Client &);
    authFunctions authentification[5];
    cmdFunctions commands[9];

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
    std::vector<File> files;

   public:
    Server(std::string port, std::string password);
    ~Server();

    // Getters
    int getServerSocket(void) const;
    std::string getPassword() const;
    int getPort() const;
    std::string getHostname() const;
    std::map<int, Client> &getMap(void);
    std::vector<File> getFiles(void) const;
    std::vector<Channel> getChannels() const;

    void printChannels();
    // Setters
    void setAuthFunctions(void);
    void setCmdFunctions(void);
    void addChannel(Channel channel);

    int checkConnections(void);
    int iterateFds(void);
    void newConnection();
    void manageUpdates(Client &client);
    void parseCommands(std::string buff, Client &client);
    void disconnectClient(Client &client);
    bool isNewChannel(std::string name);
    Channel *findChannel(std::string name);
    Client *findClient(std::string name);
    void closeChannel(Channel channel);
    std::vector<Channel> findUserChannels(Client &client);
    // Commands
    void findCommand(std::string buffer, Client &client);
    void sendResponse();
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
    void parseBot(std::string buffer, Client &client);
    void parseFileTransfer(std::string buffer, Client &sender, Client &receiver);
    void sendFile(std::vector<std::string> arguments, Client &sender, Client &receiver);
    void receiveFile(std::vector<std::string> arguments, Client &receiver, Client &sender);
};

#endif
