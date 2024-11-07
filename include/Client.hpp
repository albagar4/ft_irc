#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <ircserv.hpp>

class Client {
   private:
    int fd;
    struct sockaddr_in address;
    socklen_t address_len;
    bool auth;
    bool password;
    std::string nick;
    std::string user;
    std::string hostname;
    struct hostent* host;

   public:
    Client();
    Client(int fd, sockaddr_in address);
    ~Client();

    int getFd() const;
    sockaddr_in getAddress() const;
    bool getAuth() const;
    bool getPass() const;
    std::string getNick() const;
    std::string getUser() const;
    hostent* getHost() const;

    void setFd(int fd);
    void setAddress(sockaddr_in address);
    void setPassword(bool password);
    void setAuth(bool auth);
    void setNick(std::string nick);
    void setUser(std::string user);
    void setHostname();
};

std::ostream& operator<<(std::ostream& os, const Client& client);

#endif
