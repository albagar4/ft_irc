/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagar4 <albagar4@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:29:50 by albagar4          #+#    #+#             */
/*   Updated: 2024/11/27 11:29:52 by albagar4         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Client.hpp>
#include <Server.hpp>
#include <ircserv.hpp>

bool noParams(std::string buffer) {
    std::vector<std::string> params = split(buffer, ' ');

    if (params.size() == 4 && params[1] == "0" && params[2] == "*")
        return (false);
    return (true);
}

std::string correctChars(std::string params, int sign) {
    if (params.size() > 9 && sign == 0) return ("USERLENGTH too long\r\n");

    for (unsigned long int i = 0; i < params.size(); i++) {
        if (params.empty() || !isalnum(params[i])) {
            if (params.empty()) return ("No params provided\r\n");
            if (sign == 0 && params[i] == ' ') return ("USERNAME cannot have spaces\r\n");
            if (params[i] != '-' && params[i] != '.' && params[i] != '_') return ("Non allowed characters used\r\n");
        }
        else if (isdigit(params[0])) return ("Your USERNAME cannot start by a digit\r\n");
    }

    return ("");
}

void Server::parseUser(std::string buffer, Client &client) {
    std::string message;
    try {
        if (buffer.empty() || noParams(buffer) == true) throw ERR_NEEDMOREPARAMS;

        std::vector<std::string> params = split(buffer, ' ');
        if (!client.getUser().empty()) throw ERR_ALREADYREGISTERED;
        else {
            if (client.getNick().empty() || !correctChars(params[0], 0).empty() || !correctChars(params[3], 1).empty()) {
                if (!correctChars(params[0], 0).empty())
                    message = correctChars(params[0], 0);
                else
                    message = correctChars(params[3], 1);
                throw ERR_NOTREGISTERED;
            }
            client.setUser(params[0]);
            client.setRealname(params[3]);
        }
        client.setHostname();
        client.setAuth(true);
    }
    catch (NUM code) {
        client.setHostname();

        if (code == ERR_NEEDMOREPARAMS)
            err(ERR_NEEDMOREPARAMS, this->getHostname(), client, buffer);
        if (code == ERR_ALREADYREGISTERED)
            err(ERR_ALREADYREGISTERED, this->getHostname(), client);
        if (code == ERR_NOTREGISTERED) {
            err(ERR_NOTREGISTERED, this->getHostname(), client);
            if (client.getNick() == "")
                client.setResponse(client.getResponse() + "NICK must be setted before USER\r\n");
            else
                client.setResponse(client.getResponse() + message);
        }
    }
}
