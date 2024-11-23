#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <Client.hpp>
#include <Server.hpp>
#include <ircserv.hpp>

class Channel {
   private:
    std::string name;
    std::string password;
    std::string topic;
    std::vector<Client> clients;
    std::vector<Client> operators;
    std::vector<Client> invited;
    int userLimit;
    bool inviteOnly;
    bool opTopicOnly;
    std::string modes;
    Server *server;

   public:
    Channel();
    Channel(std::string name, std::string topic);
    ~Channel();

    // Setters
    void setName(std::string name);
    void setPassword(std::string password);
    void setTopic(std::string topic);
    void addClient(Client client);
    void addOperator(Client op);
    void addInvited(Client invited);
    void removeOperator(Client op);
    void setUserLimit(int userLimit);
    void setInviteOnly(bool inviteOnly);
    void setOpTopicOnly(bool opTopicOnly);
    void setServer(Server *server);
    // Getters
    std::string getName() const;
    std::string getPassword() const;
    std::string getTopic() const;
    std::vector<Client> getClients() const;
    std::vector<Client> getOperators() const;
    std::vector<Client> getInviteds() const;
    int getUserLimit() const;
    bool getInviteOnly() const;
    bool getOpTopicOnly() const;
    std::string getModes() const;

    bool isClient(Client client) const;
    bool isOperator(Client client) const;
    bool isInvited(Client client) const;
    void printClients();
    std::string getUserList() const;
    bool isEmpty() const;
    void disconnectClient(Client &client);
    void updateClients(Client origin, std::string response);
};

#endif
