#include <Client.hpp>
#include <Server.hpp>
#include <ircserv.hpp>

void Server::parsePass(std::string buffer, Client &client) {
    ssize_t bytes_send;
    std::string msg;

    if (this->getPassword() == buffer) {
        msg = "The password provide was correct\n";
        client.setPassword(true);
    } else
        msg = "The password you passed is incorrect\n";
    bytes_send = send(client.getFd(), msg.c_str(), msg.size(), 0);
    std::cout << "<client> <codigo de error> <resto de cosas> :<codigo de error>" << std::endl;
    if (bytes_send == -1) print_err("Pass send failed");
}
