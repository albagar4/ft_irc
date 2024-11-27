/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cap.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagar4 <albagar4@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:28:57 by albagar4          #+#    #+#             */
/*   Updated: 2024/11/27 11:29:01 by albagar4         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Client.hpp>
#include <Server.hpp>
#include <ircserv.hpp>

void Server::parseCap(std::string buffer, Client &client) {
    if (buffer == "LS" || buffer == "LS 302")
        client.setResponse("CAP * LS\r\n");
    else
        err(ERR_UNKNOWNERROR, this->getHostname(), client, "CAP{ " + buffer + "} :Command CAP must be followed by LS or LS 302");
}
