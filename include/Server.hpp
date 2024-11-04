#ifndef SERVER_HPP
#define SERVER_HPP

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
    std::vector<Client> clients;
    std::vector<struct pollfd> fds;

   public:
    Server(std::string port, std::string password);
    ~Server();

    // Getters
    int getServerSocket(void);
    // Setters

    int checkConnections(void);
    int iterateFds(void);
    void newConnection();
    //   void manageUpdates();
};

#endif
