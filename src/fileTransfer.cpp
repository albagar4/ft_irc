/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileTransfer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagar4 <albagar4@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:30:14 by albagar4          #+#    #+#             */
/*   Updated: 2024/11/27 11:30:14 by albagar4         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <File.hpp>
#include <Server.hpp>

static  std::string itoa(int number){
    std::stringstream   str;
    
    str << number;
    return (str.str());
}

static  int    validateFile(std::string filename, Server *server, std::string &aux){
    std::ifstream   file(filename.c_str());
    
    aux.clear();
    if (file.fail())
        return (101);
    aux = filename.substr(filename.find_last_of('/') + 1, filename.size());
    for (unsigned int i = 0; i < aux.size(); i++)
        if (!isalnum(aux[i]) && aux[i] != '.' && aux[i] != '_')
            return (102);
    for (unsigned int i = 0; i < server->getFiles().size(); i++)
         if (server->getFiles()[i].getFilename().compare(aux) == 0)
            return (103);
    return (0);
}

static  File    getFile(std::string file, std::string sender, std::string receiver){
   std::string  path;
   std::string  filename;

   path = file.substr(0, file.find_last_of('/'));
   filename = file.substr(file.find(file.find_last_of('/') + 1, file.size()));
   return (File(filename, path, sender, receiver));
}

void    Server::receiveFile(std::vector<std::string> arguments, Client &receiver, Client &sender){
    File    file;
    unsigned int i;
    try {
        if (arguments.size() < 4) throw 461;
        else if (arguments.size() > 4) throw 106;
        else {
            for (i = 0; i < this->files.size(); i++)
                if (this->files[i].getFilename().compare(arguments[2]) == 0){
                    file = this->files[i];
                    break ;
                }
            if (i == this->files.size()) throw 107;
            if (file.getReceiverNick() != receiver.getNick()) throw 108;
            std::fstream outFile((arguments[3] + "/" + arguments[2]).c_str(), std::fstream::out);
            if (!outFile) throw 400;
            std::fstream inFile((file.getPath() + "/" + file.getFilename()).c_str(), std::fstream::in);
            if (!inFile) throw 400 ;
            if (outFile.is_open())
                outFile << inFile.rdbuf();
            else throw 400 ;
            this->files.erase(this->files.begin() + i);
            receiver.setResponse(":NOTICE: file " + arguments[2] + " downloading\r\n");
            sender.setResponse(":NOTICE: DCC SEND accepted by " + receiver.getNick() + "\r\n");
        }

    }catch(int code){
        if (code == 461)
            receiver.setResponse(":" + receiver.getHostname() + " DDC ACCEPT :Not enough parameters.");
        if (code == 106)
            receiver.setResponse(":" + receiver.getHostname() + " DDC ACCEPT :Extra parameters.\r\n");
        if (code == 107)
            receiver.setResponse(":" + receiver.getHostname() + " DDC ACCEPT :No such file on server.\r\n");
        if (code == 108)
            receiver.setResponse(":" + receiver.getHostname() + " DDC ACCEPT :Permission Denied\r\n");
        if (code == 400)
            receiver.setResponse(":" + receiver.getHostname() + " DCC ACCEPT: An error happened while doing the file transfer\r\n");
    }
}

void Server::sendFile(std::vector<std::string> arguments, Client &sender, Client &receiver)
{
    std::string aux = "";

    try {
        if (arguments.size() < 5) throw 461;
        else if (arguments.size() > 5) throw 106;
        else {
            if (validateFile(arguments[2], this, aux)) throw validateFile(arguments[2], this, aux);
            if (arguments[3].compare(receiver.getHostname()) != 0) throw 104;
            if (arguments[4].compare(itoa(this->port)) != 0) throw 105;
            this->files.push_back(getFile(arguments[2], sender.getNick(), receiver.getNick()));
            receiver.setResponse(":NOTICE: " + sender.getNick() + " wants to send you a file: " + aux + ".\nPRIVMSG user whit 'DCC ACCEPT <filename> <path to download file>' to get the file or 'DCC IGNORE' to decline.\r\n");
            sender.setResponse(":NOTICE: DCC SEND rejected by " + receiver.getNick() + "\r\n");
        }
    } catch (int code){
        if (code == 106)
            sender.setResponse(":" + sender.getHostname() + " DDC SEND :Extra parameters.\r\n");
        if (code == 461)
            sender.setResponse(":" + sender.getHostname() + " DDC SEND :Not enough parameters.");
        if (code == 101)
            sender.setResponse(":" + sender.getHostname() + " DDC SEND :No such file.\r\n");
        if (code == 102)
            sender.setResponse(":" + sender.getHostname() + " " + aux + " :Erroneus file.\r\n");
        if (code == 103)
            sender.setResponse(":" + sender.getHostname() + " " + aux + " :File already send.\r\n");
        if (code == 104)
            sender.setResponse(":" + sender.getHostname() + " " + arguments[3] + " :The specified ip does not match the target ip.\r\n");
        if (code == 105)
            sender.setResponse(":" + sender.getHostname() + " " + arguments[4] + " :The specified port does not match the target connection port.\r\n");
    }
}

void    Server::parseFileTransfer(std::string buffer, Client &sender, Client &receiver){
    std::vector<std::string> arguments = split(buffer, ' ');
    std::string mode[4] = { "HELP", "SEND", "ACCEPT", "IGNORE"};
    unsigned int    i;

    std::cout << "Inside File Transfer: " << arguments[1] << std::endl;
    for (i = 0; i < arguments[1].size(); i++) if (arguments[1] == mode[i]) break ;
    switch (i){
        case 0:
            sender.setResponse(":" + sender.getHostname() + " NOTICE " + sender.getNick() + " :DCC <MODE> --SEND <filename> <host> <port> --ACCEPT <filename> <path to download file>  --IGNORE\r\n"); break ;
        case 1:
            sendFile(arguments, sender, receiver); break ;
        case 2:
            receiveFile(arguments, sender, receiver); break ;
        case 3:
            receiver.setResponse(":" + sender.getHostname() + " NOTICE " + sender.getNick() + " :DCC SEND rejected by " + receiver.getNick() + "\r\n");
            sender.setResponse(":" + sender.getHostname() + " NOTICE " + sender.getNick() + " :NOTICE : You reject " + receiver.getNick() + "'s file\r\n");
            break ;
        default:
            sender.setResponse(":" + sender.getHostname() + " DCC " + arguments[1] + " :Unknown command.\r\n");
    }
    std::cout << sender.getResponse() << std::endl;
}
