#ifndef SERVER_HPP
#define SERVER_HPP

#define ASCII_ART                                                              \
    "                                                                        " \
    "                                             \n"                          \
    "                                                                        " \
    "                                             \n"                          \
    "    ffffffffffffffff           tttt                                    "  \
    "iiii                                          \n"                         \
    "   f::::::::::::::::f       ttt:::t                                   "   \
    "i::::i                                         \n"                        \
    "  f::::::::::::::::::f      t:::::t                                    "  \
    "iiii                                          \n"                         \
    "  f::::::fffffff:::::f      t:::::t                                     " \
    "                                      \n"                                 \
    "  f:::::f       ffffffttttttt:::::ttttttt                            "    \
    "iiiiiii rrrrr   rrrrrrrrr       cccccccccccccccc\n"                       \
    "  f:::::f             t:::::::::::::::::t                            "    \
    "i:::::i r::::rrr:::::::::r    cc:::::::::::::::c\n"                       \
    " f:::::::ffffff       t:::::::::::::::::t                             "   \
    "i::::i r:::::::::::::::::r  c:::::::::::::::::c\n"                        \
    " f::::::::::::f       tttttt:::::::tttttt                             "   \
    "i::::i rr::::::rrrrr::::::rc:::::::cccccc:::::c\n"                        \
    " f::::::::::::f             t:::::t                                   "   \
    "i::::i  r:::::r     r:::::rc::::::c     ccccccc\n"                        \
    " f:::::::ffffff             t:::::t                                   "   \
    "i::::i  r:::::r     rrrrrrrc:::::c             \n"                        \
    "  f:::::f                   t:::::t                                   "   \
    "i::::i  r:::::r            c:::::c             \n"                        \
    "  f:::::f                   t:::::t    tttttt                         "   \
    "i::::i  r:::::r            c::::::c     ccccccc\n"                        \
    " f:::::::f                  t::::::tttt:::::t                        "    \
    "i::::::i r:::::r            c:::::::cccccc:::::c\n"                       \
    " f:::::::f                  tt::::::::::::::t                        "    \
    "i::::::i r:::::r             c:::::::::::::::::c\n"                       \
    " f:::::::f                    tt:::::::::::tt                        "    \
    "i::::::i r:::::r              cc:::::::::::::::c\n"                       \
    " fffffffff                      ttttttttttt                          "    \
    "iiiiiiii rrrrrrr                cccccccccccccccc\n"                       \
    "                                             ________________________   " \
    "                                             \n"                          \
    "                                             _::::::::::::::::::::::_   " \
    "                                             \n"                          \
    "                                             ________________________   " \
    "                                             \n"                          \
    "                                                                        " \
    "                                             \n"                          \
    "                                                                        " \
    "                                             \n"

#include <Client.hpp>
#include <ircserv.hpp>

class Server {
   private:
    Server() {};
    void createServerSocket(void);
    std::string password;
    int port;
    int serverSocket;
    sockaddr_in serverAddress;
    // std::vector<Client> clients;
    std::vector<struct pollfd> fds;
    std::map<int, Client> map;

   public:
    Server(std::string port, std::string password);
    ~Server();

    // Getters
    int getServerSocket(void) const;
    std::string getPassword() const;
    int getPort() const;
    std::vector<Client> getClients() const;
    // Setters

    int checkConnections(void);
    int iterateFds(void);
    void newConnection();
    void manageUpdates(Client &client);
    void parseCommands(char *buffer, Client &client);

    // Commands
    void parseCap(char *buffer, Client &client);
    void parsePass(char *buffer, Client &client);
    void parseNick(char *buffer, Client &client);
    void parseUser(char *buffer, Client &client);
    // void parseCap(char *buffer, Client &client);
    // void parseCap(char *buffer, Client &client);
};

std::ostream& operator<<(std::ostream& os, const Server& server);
#endif
