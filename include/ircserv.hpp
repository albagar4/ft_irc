#ifndef IRCSERV_HPP
#define IRCSERV_HPP

#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <poll.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#define RESET "\033[0m"
#define BLACK "\033[30m"   /* Black */
#define RED "\033[31m"     /* Red */
#define GREEN "\033[32m"   /* Green */
#define YELLOW "\033[33m"  /* Yellow */
#define BLUE "\033[34m"    /* Blue */
#define MAGENTA "\033[35m" /* Magenta */
#define CYAN "\033[36m"    /* Cyan */
#define WHITE "\033[37m"   /* White */

enum NUM {
    ERR_NOSUCHNICK = 401,        // "<nickname> :No such nick/channel"
    ERR_NOSUCHSERVER = 402,      // "<server name> :No such server"
    ERR_NOSUCHCHANNEL = 403,     // "<channel name> :No such channel"
    ERR_CANNOTSENDTOCHAN = 404,  // "<channel name> :Cannot send to channel"
    ERR_TOOMANYCHANNELS = 405,   // "<channel name> :You have joined too many channels"
    ERR_WASNOSUCHNICK = 406,     // "<nickname> :There was no such nickname"
    ERR_TOOMANYTARGETS = 407,    // "<target> :Duplicate recipients. No message delivered"
    ERR_NOORIGIN = 409,          // ":No origin specified"
    ERR_NORECIPIENT = 411,       // ":No recipient given (<command>)"
    ERR_NOTEXTTOSEND = 412,      // ":No text to send"
    ERR_NOTOPLEVEL = 413,        // "<mask> :No toplevel domain specified"
    ERR_WILDTOPLEVEL = 414,      // "<mask> :Wildcard in toplevel domain"
    ERR_BADMASK = 415,           // "<mask> :Bad Server/host mask"

    ERR_UNKNOWNCOMMAND = 421,  // "<command> :Unknown command"
    ERR_NOMOTD = 422,          // ":MOTD File is missing"
    ERR_NOADMININFO = 423,     // "<server> :No administrative info available"
    ERR_FILEERROR = 424,       // ":File error doing <file op> on <file>"

    ERR_NONICKNAMEGIVEN = 431,   // ":No nickname given"
    ERR_ERRONEUSNICKNAME = 432,  // "<nick> :Erroneous nickname"
    ERR_NICKNAMEINUSE = 433,     // "<nick> :Nickname is already in use"
    ERR_NICKCOLLISION = 436,     // "<nick> :Nickname collision KILL"
    ERR_UNAVAILRESOURCE = 437,   // "<nick/channel> :Nick/channel is temporarily unavailable"

    ERR_USERNOTINCHANNEL = 441,  // "<nick> <channel> :They aren't on that channel"
    ERR_NOTONCHANNEL = 442,      // "<channel> :You're not on that channel"
    ERR_USERONCHANNEL = 443,     // "<user> <channel> :is already on channel"
    ERR_NOLOGIN = 444,           // "<user> :User not logged in"
    ERR_SUMMONDISABLED = 445,    // ":SUMMON has been disabled"
    ERR_USERSDISABLED = 446,     // ":USERS has been disabled"

    ERR_NOTREGISTERED = 451,      // ":You have not registered"
    ERR_NEEDMOREPARAMS = 461,     // "<command> :Not enough parameters"
    ERR_ALREADYREGISTERED = 462,  // ":You may not reregister"
    ERR_PASSWDMISMATCH = 464,     // ":Password incorrect"
    ERR_YOUREBANNEDCREEP = 465,   // ":You are banned from this server"
    ERR_YOUWILLBEBANNED = 466,    // ":You will be banned"
    ERR_KEYSET = 467,             // "<channel> :Channel key already set"
    ERR_CHANNELISFULL = 471,      // "<channel> :Cannot join channel (+l)"
    ERR_UNKNOWNMODE = 472,        // "<char> :is unknown mode char to me"
    ERR_INVITEONLYCHAN = 473,     // "<channel> :Cannot join channel (+i)"
    ERR_BANNEDFROMCHAN = 474,     // "<channel> :Cannot join channel (+b)"
    ERR_BADCHANNELKEY = 475,      // "<channel> :Cannot join channel (+k)"
    ERR_BADCHANMASK = 476,        // "<channel> :Bad Channel Mask"
    ERR_NOCHANMODES = 477,        // "<channel> :Channel doesn't support modes"
    ERR_BANLISTFULL = 478,        // "<channel> <banmask> :Ban list is full"

    ERR_NOPRIVILEGES = 481,      // ":Permission Denied- You're not an IRC operator"
    ERR_CHANOPRIVSNEEDED = 482,  // "<channel> :You're not channel operator"
    ERR_CANTKILLSERVER = 483,    // ":You can't kill a server!"
    ERR_RESTRICTED = 484,        // ":Your connection is restricted!"
    ERR_UNIQOPRIVSNEEDED = 485,  // ":You're not the original channel operator"
    ERR_NOOPERHOST = 491,        // ":No O-lines for your host"

    ERR_UMODEUNKNOWNFLAG = 501,  // ":Unknown MODE flag"
    ERR_USERSDONTMATCH = 502,    // ":Cannot change mode for other users"

    ERR_HELPNOTFOUND = 524,   // "<command> :Help not found"
    ERR_INVALIDCAPCMD = 410,  // ":Invalid CAP command"
    ERR_NICKLOCKED = 902,     // ":You must use a registered nick to perform this command"
    ERR_SASLFAIL = 904,       // ":SASL authentication failed"
    ERR_SASLTOOLONG = 905,    // ":SASL message too long"
    ERR_SASLABORTED = 906,    // ":SASL authentication aborted"
    ERR_SASLALREADY = 907,    // ":You have already authenticated using SASL"

    ERR_UNKNOWN = 999  // Generic unknown error
};

extern std::map<NUM, std::string> errorMessages;

class Server;
class Client;

void ft_print(std::string str);
void ft_print(std::string str, const char* color);
void print_err(std::string errorMessage);
void printHelp();
void printLaunchServer(const Server& server);
void printConnected(Client client);
void printDisconnected(Client client);
void printCloseServer();
std::vector<std::string> split(std::string input, char delimiter);
std::string fixSpaces(std::string buffer);
void initializeErrorMessages();
std::string errorResponse(std::string hostname, NUM code);

#endif
