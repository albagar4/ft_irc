#include <Channel.hpp>

Channel::Channel() {
    this->name = "";
    this->topic = "";
}
Channel::Channel(std::string name, std::string topic) {
    this->name = name;
    this->topic = topic;
}
Channel::~Channel() {}

void Channel::setName(std::string name) { this->name = name; }
void Channel::setPassword(std::string password) { this->password = password; }
void Channel::setTopic(std::string topic) { this->topic = topic; }
void Channel::addClient(Client client) {
    for (size_t i = 0; i != this->clients.size(); i++) {
        if (client.getFd() == this->clients[i].getFd()) return;
    }
    if (this->clients.size() == 0) {
        addOperator(client);
    }
    this->clients.push_back(client);
}
void Channel::addOperator(Client op) {
    for (size_t i = 0; i != this->operators.size(); i++) {
        if (op.getFd() == this->operators[i].getFd()) return;
    }
    this->operators.push_back(op);
}
void Channel::setUserLimit(int userLimit) { this->userLimit = userLimit; }
void Channel::setInviteOnly(bool inviteOnly) { this->inviteOnly = inviteOnly; }

std::string Channel::getName() const { return this->name; }
std::string Channel::getPassword() const { return this->password; }
std::string Channel::getTopic() const { return this->topic; }
std::vector<Client> Channel::getClients() const { return this->clients; }
std::vector<Client> Channel::getOperators() const { return this->operators; }
int Channel::getUserLimit() const { return this->userLimit; }
bool Channel::getInviteOnly() const { return this->inviteOnly; }
std::string Channel::getUserList() const {
    std::string list = "";
    for (size_t i = 0; i < this->clients.size(); i++) {
        if (this->isOperator(this->clients[i]) == true) list += "@";
        list += this->clients[i].getNick();
        list += " ";
    }
    return list;
}

void Channel::printClients() {
    for (size_t i = 0; i < this->clients.size(); i++) {
        std::cout << this->clients[i].getHost()->h_name;
        if (isOperator(this->clients[i]) == true) {
            std::cout << " [op]";
        }
        std::cout << ",";
    }
}

bool Channel::isOperator(Client client) const {
    for (size_t i = 0; i < this->operators.size(); i++) {
        if (client.getFd() == this->operators[i].getFd()) return true;
    }
    return false;
}
