#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <Client.hpp>
#include <ircserv.hpp>

class Channel {
   private:
    std::string name;
    std::string password;
    std::string topic;
    std::vector<Client> clients;
    std::vector<Client> operators;
    int userLimit;
    bool inviteOnly;

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
    void setUserLimit(int userLimit);
    void setInviteOnly(bool inviteOnly);
    // Getters
    std::string getName() const;
    std::string getPassword() const;
    std::string getTopic() const;
    std::vector<Client> getClients() const;
    std::vector<Client> getOperators() const;
    int getUserLimit() const;
    bool getInviteOnly() const;
    bool isOperator(Client client) const;
    void printClients();
    std::string getUserList() const;
};

#endif
