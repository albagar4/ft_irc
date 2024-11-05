#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <ircserv.hpp>

class Client {
private:
    int fd;
    std::string address;
    bool auth;
    bool password;
    std::string nick;
    std::string user;
public:
    Client();
    Client(int fd, std::string address);
    ~Client();

    int getFd() const;
    std::string getAddress() const;
    bool getAuth() const;
    bool getPass() const;
    std::string getNick() const;
    std::string getUser() const;

    void setFd(int fd);
    void setAddress(std::string address);
    void setPassword(bool password);
    void setAuth(bool auth);
    void setNick(std::string nick);
    void setUser(std::string user);
};

std::ostream& operator<<(std::ostream& os, const Client& client);

#endif
