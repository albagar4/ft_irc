#include <ircserv.hpp>
#include <Server.hpp>

int main(int argc, char **argv) {
  if (argc != 3)
    print_err("Incorrect nbr of parameters\nUsage: ./ircserv <port> <password>");
  else {
    Server server(argv[1], argv[2]);

    while (true) {
      if (server.checkConnections() > 0) {
        server.iterateFds();
        // parseResponse(int i)
        // executeResponse(int i)
      }
    }
  }
  return 0;
}
