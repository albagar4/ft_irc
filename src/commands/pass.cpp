/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagar4 <albagar4@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:29:32 by albagar4          #+#    #+#             */
/*   Updated: 2024/11/27 11:29:33 by albagar4         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Client.hpp>
#include <Server.hpp>
#include <ircserv.hpp>

bool isEmpty(std::string buffer) {
    for (unsigned long int i = 0; i < buffer.size(); i++)
        if (buffer[i] != ' ' && buffer[i] != '\t' && buffer[i] != '\0')
            return (false);
    return (true);
}

void Server::parsePass(std::string buffer, Client &client) {
    std::string msg;
    client.setHostname();
    
    if (this->getPassword() == buffer && client.getPass() == false)
        client.setPassword(true);
    else if (client.getPass() == true)
        err(ERR_ALREADYREGISTERED, this->getHostname(), client);
    else if (isEmpty(buffer) == true)
        err(ERR_NEEDMOREPARAMS, this->getHostname(), client);
    else {
        err(ERR_PASSWDMISMATCH, this->getHostname(), client);
        client.setRetries(client.getRetries() - 1);

        std::stringstream ss;
        ss << client.getRetries();
        msg = "Nbr of retries left: " + ss.str() + "\r\n";
        client.setResponse(client.getResponse() + msg);
    }

    if (client.getRetries() == 0) {
        sendResponse();
        this->disconnectClient(client);
    }
}
