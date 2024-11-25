#include <Server.hpp>
#include <ircserv.hpp>

int g_signal = 0;

void signalHandler(int signum) { g_signal = signum; }

int main(int argc, char **argv) {
    if (argc != 3)
        print_err("Incorrect nbr of parameters\nUsage: ./ircserv <port> <password>");
    else {
        signal(SIGINT, signalHandler);
        signal(SIGQUIT, signalHandler);
        Server server(argv[1], argv[2]);
        initializeErrorMessages();
        while (!g_signal) {
            if (server.checkConnections() > 0) {
                server.iterateFds();
            }
        }
    }
    return 0;
}
