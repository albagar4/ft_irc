#ifndef CLIENT_HPP
# define CLIENT_HPP

#include <ircserv.hpp>

class Client {
private:
  int fd;
  std::string address;
public:
  Client();
  Client(int fd, std::string address);
  ~Client();
  int getFd();
  std::string getAddress();
  void setFd(int fd);
  void setAddress(std::string address);

};

#endif
