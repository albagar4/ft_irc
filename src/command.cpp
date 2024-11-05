#include <Client.hpp>
#include <Server.hpp>
#include <ircserv.hpp>

void Server::parseCap(std::string buffer, Client &client) {
    (void)client;
    ft_print("Inside Cap: ");
    ft_print(buffer);
};

void Server::parsePass(std::string buffer, Client &client) {
	ssize_t bytes_send;
	std::string msg;

	if (this->getPassword() == buffer) {
		msg = "The password provide was correct\n";
		client.setPassword(true);
	}
	else
		msg = "The password you passed is incorrect\n";
	bytes_send = send(client.getFd(), msg.c_str(), msg.size(), 0);
	std::cout << "<client> <codigo de error> <resto de cosas> :<codigo de error>" << std::endl;
	if (bytes_send == -1)
		print_err("Pass send failed");
};
void Server::parseNick(std::string buffer, Client &client) {
    (void)client;
    ft_print("Inside Nick: ");
    ft_print(buffer);
};
void Server::parseUser(std::string buffer, Client &client) {
    (void)client;
    ft_print("Inside User: ");
    ft_print(buffer);
};
void Server::parseJoin(std::string buffer, Client &client) {
    (void)client;
    ft_print("Inside Join: ");
    ft_print(buffer);
};
void Server::parsePart(std::string buffer, Client &client) {
    (void)client;
    ft_print("Inside Part: ");
    ft_print(buffer);
};

void Server::parseKick(std::string buffer, Client &client) {
    (void)client;
    ft_print("Inside Kick: ");
    ft_print(buffer);
};
void Server::parseInvite(std::string buffer, Client &client) {
    (void)client;
    ft_print("Inside Invite: ");
    ft_print(buffer);
};
void Server::parseTopic(std::string buffer, Client &client) {
    (void)client;
    ft_print("Inside Topic: ");
    ft_print(buffer);
};
void Server::parseMode(std::string buffer, Client &client) {
    (void)client;
    ft_print("Inside Mode: ");
    ft_print(buffer);
};
void Server::parsePrivMsg(std::string buffer, Client &client) {
    (void)client;
    ft_print("Inside PrivMsg: ");
    ft_print(buffer);
};

void Server::parseQuit(std::string buffer, Client &client) {
    (void)client;
    ft_print("Inside Quit: ");
    ft_print(buffer);
};
