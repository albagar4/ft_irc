#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <ircserv.hpp>

class Client {
   private:
    int fd;
    std::string address;

   public:
    Client();
    Client(int fd, std::string address);
    ~Client();
    int getFd() const;
    std::string getAddress() const;
    void setFd(int fd);
    void setAddress(std::string address);
};

std::ostream& operator<<(std::ostream& os, const Client& client);

#endif
