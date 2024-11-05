#include <Client.hpp>
#include <Server.hpp>
#include <ircserv.hpp>

void ft_print(std::string str) { std::cout << str << std::endl; }

void ft_print(std::string str, const char* color) {
    std::cout << color;
    std::cout << str << std::endl;
    std::cout << RESET;
}

void print_err(std::string errorMessage) {
    std::cout << RED;
    std::cerr << errorMessage << std::endl;
    std::cout << RESET;
    exit(1);
}

void printHelp() {
    std::cout << GREEN;
    std::cout << "The avaliable commands are:\n";
    std::cout << "\tCAP\n";
    std::cout << "\tPASS\n";
    std::cout << "\tNICK\n";
    std::cout << "\tUSER\n";
    std::cout << "\tJOIN\n";
    std::cout << "\tPART\n";
    std::cout << "\tKICK\n";
    std::cout << "\tINVITE\n";
    std::cout << "\tTOPIC\n";
    std::cout << "\tMODE\n";
    std::cout << "\tPRIVMSG\n";
    std::cout << "\tQUIT\n";
    std::cout << RESET;
}

void printConnected(Client client) {
    std::cout << BLUE;
    std::cout << "Client " << client.getAddress() << " connected in socket "
              << client.getFd() << "\n";
    std::cout << RESET;
}

void printDisconnected(Client client) {
    std::cout << YELLOW;
    std::cout << "Client " << client.getAddress()
              << " was disconnected from socket " << client.getFd() << "\n";
    std::cout << RESET;
}

void printCloseServer() {
    std::cout << MAGENTA;
    std::cout << "Server was closed\n";
    std::cout << RESET;
}
