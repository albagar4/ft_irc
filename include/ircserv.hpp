#ifndef IRCSERV_HPP
# define IRCSERV_HPP

#include <iostream>
#include <string>
#include <string.h>
#include <iomanip>
#include <stdlib.h>
#include <stdint.h>
#include <cstdio>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <poll.h>
#include <arpa/inet.h>

void ft_print(std::string str);
void print_err(std::string errorMessage);

#endif
