#include <ircserv.hpp>

void ft_print(std::string str) { std::cout << str << std::endl; }

void print_err(std::string errorMessage) {
    std::cerr << errorMessage << std::endl;
    exit(1);
}
