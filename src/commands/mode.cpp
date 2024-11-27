/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagar4 <albagar4@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:29:18 by albagar4          #+#    #+#             */
/*   Updated: 2024/11/27 11:29:20 by albagar4         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Client.hpp>
#include <Server.hpp>
#include <ircserv.hpp>

static char addMode(Channel &channel, char mode, std::vector<std::string> tokens) {
    switch (mode) {
        case 'i':
            channel.setInviteOnly(true);
            return mode;
        case 't':
            channel.setOpTopicOnly(true);
            return mode;
        case 'k':
            if (tokens.size() != 3) throw ERR_NEEDMOREPARAMS;
            channel.setPassword(tokens[2]);
            return mode;
        case 'o': {
            if (tokens.size() != 3) throw ERR_NEEDMOREPARAMS;
            std::vector<Client> clients = channel.getClients();
            std::vector<Client>::iterator it = clients.begin();
            for (; it != clients.end(); it++) {
                if (it->getNick() == tokens[2]) {
                    channel.addOperator(*it);
                    return mode;
                }
            }
            throw ERR_USERNOTINCHANNEL;
            return 0;
        }
        case 'l': {
            if (tokens.size() != 3) throw ERR_NEEDMOREPARAMS;
            int userLimit = atoi(tokens[2].c_str());
            if (userLimit < 1 || userLimit > 99) throw ERR_UNKNOWNMODE;
            channel.setUserLimit(userLimit);
            return mode;
        }
        default:
            throw ERR_UNKNOWNMODE;
            return 0;
    }
}
static char removeMode(Client &client, Channel &channel, char mode,
                       std::vector<std::string> tokens) {
    switch (mode) {
        case 'i':
            channel.setInviteOnly(false);
            return mode;
        case 't':
            channel.setOpTopicOnly(false);
            return mode;
        case 'k':
            channel.setPassword("");
            return mode;
        case 'o': {
            if (tokens.size() != 3) throw ERR_NEEDMOREPARAMS;
            std::vector<Client> operators = channel.getOperators();
            std::vector<Client>::iterator it = operators.begin();
            for (; it != operators.end(); it++) {
                if (it->getNick() == tokens[2]) {
                    if (client.getNick() == it->getNick()) throw ERR_UNKNOWNMODE;
                    channel.removeOperator(*it);
                    return mode;
                }
            }
            throw ERR_USERNOTINCHANNEL;
            return 0;
        }; break;
        case 'l':
            channel.setUserLimit(99);
            return mode;
        default:
            throw ERR_UNKNOWNMODE;
            return 0;
    }
}

void Server::parseMode(std::string buffer, Client &client) {
    Channel *tempChannel;
    std::vector<std::string> tokens = split(buffer, ' ');

    try {
        if (!tokens.size()) throw ERR_NEEDMOREPARAMS;
        tempChannel = this->findChannel(tokens[0]);
        if (!tempChannel) throw ERR_NOSUCHCHANNEL;
        if (tokens.size() == 1) throw RPL_CHANNELMODEIS;
        if (!tempChannel->isOperator(client)) throw ERR_CHANOPRIVSNEEDED;
        size_t i = 0;
        std::string successfulModes;
        try {
            for (; i < tokens[1].size(); i++) {
                if (tokens[1][i] == '+') {
                    successfulModes = '+';
                    while (++i < tokens[1].size() && tokens[1][i] != '-')
                        successfulModes += addMode(*tempChannel, tokens[1][i], tokens);
                } else if (tokens[1][i] == '-') {
                    successfulModes = '-';
                    while (++i < tokens[1].size() && tokens[1][i] != '+')
                        successfulModes += removeMode(client, *tempChannel, tokens[1][i], tokens);
                } else {
                    throw ERR_UNKNOWNMODE;
                }
            }
            throw SUCCESS;
        } catch (NUM code) {
            if (code == SUCCESS) {
                client.setResponse(client.getResponse() + ":" + client.getHostname() + " MODE " +
                                   tempChannel->getName() + " " + successfulModes);
                if (tokens.size() == 3) client.setResponse(client.getResponse() + " " + tokens[2]);
                client.setResponse(client.getResponse() + "\r\n");
                tempChannel->updateClients(client, client.getResponse());
            } else if (code == ERR_USERNOTINCHANNEL)
                err(ERR_USERNOTINCHANNEL, this->getHostname(), client, tokens[2]);
            else if (code == ERR_UNKNOWNMODE)
                err(ERR_UNKNOWNMODE, this->getHostname(), client, &tokens[1][i]);
            else if (code == ERR_NEEDMOREPARAMS)
                throw ERR_NEEDMOREPARAMS;
        }
    } catch (NUM code) {
        if (code == RPL_CHANNELMODEIS)
            client.setResponse(client.getResponse() + ":" + this->getHostname() + " 324 " +
                               client.getNick() + " " + tempChannel->getName() + " " +
                               tempChannel->getModes() + "\r\n");
        else if (code == ERR_NEEDMOREPARAMS)
            err(ERR_NEEDMOREPARAMS, this->getHostname(), client, "MODE");
        else if (code == ERR_NOSUCHCHANNEL)
            err(ERR_NOSUCHCHANNEL, this->getHostname(), client, tokens[0]);
        else if (code == ERR_CHANOPRIVSNEEDED)
            err(ERR_CHANOPRIVSNEEDED, this->getHostname(), client, tempChannel->getName());
    }
}
