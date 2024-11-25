#include <Channel.hpp>

Channel::Channel() {
    this->name = "";
    this->topic = "";
    this->password = "";
    this->userLimit = 99;
    this->inviteOnly = false;
    this->opTopicOnly = false;
}

Channel::Channel(std::string name, std::string topic) {
    this->name = name;
    this->topic = topic;
    this->password = "";
    this->userLimit = 99;
    this->inviteOnly = false;
    this->opTopicOnly = false;
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
void Channel::addInvited(Client invited) {
    for (size_t i = 0; i != this->invited.size(); i++) {
        if (invited.getFd() == this->invited[i].getFd()) return;
    }
    this->invited.push_back(invited);
}
void Channel::removeOperator(Client op) {
    for (std::vector<Client>::iterator it = this->operators.begin(); it != this->operators.end();
         it++) {
        if (op.getFd() == it->getFd()) {
            this->operators.erase(it);
            return;
        }
    }
}
void Channel::removeInvited(Client invited) {
    for (std::vector<Client>::iterator it = this->invited.begin(); it != this->invited.end();
         it++) {
        if (invited.getFd() == it->getFd()) {
            this->invited.erase(it);
            return;
        }
    }
}
void Channel::setUserLimit(int userLimit) { this->userLimit = userLimit; }
void Channel::setInviteOnly(bool inviteOnly) { this->inviteOnly = inviteOnly; }
void Channel::setOpTopicOnly(bool opTopicOnly) { this->opTopicOnly = opTopicOnly; }
void Channel::setServer(Server *server) { this->server = server; }

std::string Channel::getName() const { return this->name; }
std::string Channel::getPassword() const { return this->password; }
std::string Channel::getTopic() const { return this->topic; }
std::vector<Client> &Channel::getClients() { return this->clients; }
std::vector<Client> Channel::getOperators() const { return this->operators; }
std::vector<Client> Channel::getInviteds() const { return this->invited; }
int Channel::getUserLimit() const { return this->userLimit; }
bool Channel::getInviteOnly() const { return this->inviteOnly; }
bool Channel::getOpTopicOnly() const { return this->opTopicOnly; }

std::string Channel::getModes() const {
    std::string modes = "";
    std::ostringstream ss;
    ss << this->getUserLimit();
    if (this->getInviteOnly()) modes += "i";
    if (this->getOpTopicOnly()) modes += "t";
    if (!this->getPassword().empty()) modes += "k";
    if (this->getUserLimit() != 99) modes += "l " + ss.str();
    if (!modes.empty()) modes = "+" + modes;
    return modes;
}
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
bool Channel::isClient(Client client) const {
    for (size_t i = 0; i < this->clients.size(); i++) {
        if (client.getFd() == this->clients[i].getFd()) return true;
    }
    return false;
}
bool Channel::isOperator(Client client) const {
    for (size_t i = 0; i < this->operators.size(); i++) {
        if (client.getFd() == this->operators[i].getFd()) return true;
    }
    return false;
}
bool Channel::isInvited(Client client) const {
    for (size_t i = 0; i < this->invited.size(); i++) {
        if (client.getFd() == this->invited[i].getFd()) return true;
    }
    return false;
}
bool Channel::isEmpty() const {
    if (this->clients.empty() == true) return true;
    return false;
}

void Channel::disconnectClient(Client &client) {
    for (size_t i = 0; i < this->clients.size(); i++) {
        if (this->clients[i].getFd() == client.getFd()) {
            if (this->isOperator(client) == true) {
                this->removeOperator(client);
            }
            this->clients.erase(this->clients.begin() + i);
            return;
        }
    }
}
void Channel::updateClients(Client origin, std::string response) {
    std::vector<Client>::iterator it = this->clients.begin();
    for (; it != this->clients.end(); it++) {
        if (it->getFd() != origin.getFd()) {
            it->setResponse(response);
            if (this->server) {
                std::map<int, Client> &clientMap = this->server->getMap();
                std::map<int, Client>::iterator mapIt = clientMap.find(it->getFd());
                if (mapIt != clientMap.end()) mapIt->second.setResponse(it->getResponse());
            }
        }
    }
}
