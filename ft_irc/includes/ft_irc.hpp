#pragma once

#include "../src/user/User.hpp"
#include "../src/server/Server.hpp"
#include "../src/channel/Channel.hpp"
#include "../src/exceptionIRC/ExceptionIRC.hpp"
#include "../src/exceptionIRC/replyList.hpp"

#include <iostream>
#include <string.h>
#include <string>
#include <sstream>
#include <sys/socket.h>
#include <sys/types.h>
#include <map>
#include <netinet/in.h> //for sockaddr_in
#include <fcntl.h>
#include <unistd.h>
#include <poll.h>
#include <csignal>
#include <vector>
#include <set>
#include <cstdlib>
#include <csignal>

#ifndef DEBUG_MODE
# define DEBUG_MODE 0
#endif

#define MAX_COMMAND_LENGTH 512

typedef std::vector<std::string>	command;
typedef std::vector<command>	commands;
class Server;

enum	commandName {
	CAP,
	PASS,
	NICK,
	USER,
	PING,
	QUIT,
	PRIVMSG,
	JOIN,
	KICK,
	INVITE,
	TOPIC,
	MODE,
	WHO,
	PRINT
};

// DEBUG
void	debugPrint(command &argv, std::map<int, User *> &users, int socketFd, MembershipRelation &membership);

// EXECUTE COMMANDS

void	sendToUsers(const User &sender, const std::vector<Connection *> &channelUsers, const std::string &message);
void	handleCap(command &argv, User &currentUser);
void	handlePassword(command &argv, User &user, const std::string &serverPassword);
void	handleNick(command &argv, std::map<int, User *> &users, int socketFd, MembershipRelation &membership);
void	handleUser(command &argv, User &currentUser);
void	handlePing(command &argv, User &user);
void	handlePrivmsg(command &argv, std::map<int, User *> &users, int socketFd, MembershipRelation &membership);
void	handleJoin(command &argv, std::map<int, User *> &users, int socketFd, MembershipRelation &membership);
void	handleMode(command &argv, std::map<int, User *> &users, int socketFd, MembershipRelation &membership);
void	handleWho(command &argv, User &user, MembershipRelation &membership);

// LOG COMMANDS

void	logCommandToUser(const std::string &command, const User &receiver);
void	logCommandToServer(const std::string &command, const User &sender);

// PARSING

void	parseMessage(const std::map<const std::string, enum commandName> commandNames, std::map<int, User *> &users, int socketFd, MembershipRelation &membership, const std::string &serverPassword, std::set<int> &fdsToRemove);

// BUILD COMMANDS

std::string	buildCommand(const std::string &senderUserInfo, const char *command, const std::string &parameters);
std::string	buildDeliverMessage(const std::string &senderUserInfo, const std::string &recipientName, const std::string &message);
std::string	buildWelcomeMessage(const std::string &recipientNickname);
std::string	buildMessageOfTheDay(const std::string &recipientNickname);