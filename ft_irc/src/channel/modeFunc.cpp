#include "./Channel.hpp"
#include "../includes/ft_irc.hpp"
#include <queue>
#include <utility>

static std::queue<std::pair<std::string, std::string> > parseModes(command &argv, bool &addMode, std::map<int, User *> &users, int socketFd);
void modeO(bool addMode, Channel *channel, User *requester, User *toOp, const std::vector<Connection *> &channelUsers);
void modeK(bool addMode, Channel *channel, const std::string &password, User *requester, const std::vector<Connection *> &channelUsers);
void modeL(bool addMode, Channel *channel, User *requester, std::string limitGiven, const std::vector<Connection *> &channelUsers);

/*
channel modes
MODE <channel> {[+|-]|o|i|t|k|l} [<limit>] [<user>] [<ban mask>]

	1. Check if user is authenticated, if not throw ERR_NOTREGISTERED
	2. Check if there is at least one parameter, if not throw ERR_NEEDMOREPARAMS
	3. Check if channel exists, if not throw ERR_NOSUCHCHANNEL
	4. Check if user is in channel, if not throw ERR_NOTONCHANNEL
	5. Check if user is channel operator, if not throw ERR_CHANOPRIVSNEEDED
	6. Parse modes from argv into a queue of pairs (mode, parameter)
	7. For each mode in the queue:
		- If mode is 'o', give/take operator status from/to user
		- If mode is 'k', set/remove channel password
		- If mode is 'l', set/remove channel user limit
		- If mode is 'i', toggle invite-only status
		- If mode is 't', toggle topic settable by op only status
		- If mode is unknown, throw ERR_UNKNOWNMODE
	8. To all users in channel send which modes were changed successfully
*/
void handleMode(command &argv, std::map<int, User *> &users, int socketFd, MembershipRelation &membership) {
	// 1.
	if (!users[socketFd]->getAuthenticationStatus())
		throw exceptionIRC(ERR_NOTREGISTERED, ERRDESC_NOTREGISTERED);
	// 2.
	if (argv.size() < 2) 
		throw exceptionIRC(ERR_NEEDMOREPARAMS, ERRDESC_NEEDMOREPARAMS, "MODE");
	// 3.
	Channel *channel = membership.getChannelByName(argv[1]);
	if (channel == NULL)
		throw exceptionIRC(ERR_NOSUCHCHANNEL, ERRDESC_NOSUCHCHANNEL, argv[1]);
	// 4.
	const std::vector<Connection *>	&channelUsers = membership.getChannelUsers(channel);
	if (!MembershipRelation::isUserInChannel(users[socketFd], channelUsers))
		throw exceptionIRC(ERR_NOTONCHANNEL, ERRDESC_NOTONCHANNEL, argv[1]);
	// 5.
	if (!MembershipRelation::isUserAnOperator(users[socketFd], channelUsers))
		throw exceptionIRC(ERR_CHANOPRIVSNEEDED, ERRDESC_CHANOPRIVSNEEDED, argv[1]);

	// 6.
	command fromModes(argv.begin() + 2, argv.end());
	bool	addMode;
	std::queue<std::pair<std::string, std::string> > modes = parseModes(fromModes, addMode, users, socketFd);

	std::string mods;
	std::string params;

	// 7.
	User	*user;
	while (!modes.empty()) {
		try {
			switch (modes.front().first.at(0)) {
				case 'o':
					user = User::getUserByNickname(users, modes.front().second);
					if (!user)
						throw exceptionIRC(ERR_NOSUCHNICK, ERRDESC_NOSUCHNICK, modes.front().second);
					modeO(addMode, channel, users[socketFd], user, channelUsers);
					mods.append("o");
					params.append(modes.front().second + " ");
					break;
				case 'k':
					modeK(addMode, channel, modes.front().second, users[socketFd], channelUsers);
					mods.append("k");
					params.append(modes.front().second + " ");
					break;
				case 'l':
					modeL(addMode, channel, users[socketFd], modes.front().second, channelUsers);
					mods.append("l");
					if (ft_atoi(modes.front().second) == 0)
						modes.front().second = "0";
					if (addMode)
						params.append(modes.front().second + " ");
					break;
				case 'i':
					if ((addMode && channel->getInvOnlyStatus()) || (!addMode && !channel->getInvOnlyStatus())) {
						throw exceptionIRC(ERR_EMPTYLINE, ERRDESC_EMPTYLINE);
					}
					channel->setInvOnlyStatus(addMode);
					mods.append("i");
					break;
				case 't':
					if ((addMode && channel->getTopicSettableByOpOnly()) || (!addMode && !channel->getTopicSettableByOpOnly())) {
						throw exceptionIRC(ERR_EMPTYLINE, ERRDESC_EMPTYLINE);
					}
					channel->setTopicSettableByOpOnly(addMode);
					mods.append("t");
					break;
				default:
					throw exceptionIRC(ERR_UNKNOWNMODE, ERRDESC_UNKNOWNMODE, std::string(1, modes.front().first.at(0)));
			}
			modes.pop();
		} catch (const exceptionIRC &e) {
			std::string errorMessage = e.buildErrorMessage(users[socketFd]->getNickname());
			users[socketFd]->enqueueMessage(errorMessage);
			logCommandToUser(errorMessage, *users[socketFd]);
			modes.pop();
		}
	}
	if (mods.empty())
		return;

	// 8.
	std::string modesAndParams = addMode ? "+" : "-";
	modesAndParams.append(mods + " " + params);

	std::string modesChanged = buildCommand(users[socketFd]->getSenderInfo(), "MODE", channel->getName() + " " + modesAndParams);
	sendToUsers(*users[socketFd], channelUsers, modesChanged);
}

#define SUPPORTED_MODES "iotkl"
#define PLUS_MODES_EXPECTING_ARGUMENT "okl"
#define MINUS_MODES_EXPECTING_ARGUMENT "ok"

/*
	1. Check if first character is + or - and set addMode accordingly
	2. Check if mode is supported, if not throw ERR_UNKNOWNMODE
	3. Set modeAndParameter with mode and parameter if needed, else set parameter to empty string
	4. Push mode with parameter to result queue and clear modeAndParameter for next iteration
*/
static std::queue<std::pair<std::string, std::string> > parseModes(command &argv, bool &addMode, std::map<int, User *> &users, int socketFd) {
	std::queue<std::pair<std::string, std::string> > result;
	std::pair<std::string, std::string> modeAndParameter;

	// 1.
	if (argv[0].at(0) != '+' && argv[0].at(0) != '-') {
		throw exceptionIRC(ERR_UNKNOWNMODE, ERRDESC_UNKNOWNMODE, std::string(1, argv[0].at(0)));
	}
	addMode = (argv[0].at(0) == '+');

	std::string modesGiven = argv[0].substr(1);
	int parameterIndex = 1;
	for (size_t i = 0; i < modesGiven.length(); i++) {
		// 2.
		try {
			if (isIn(modesGiven[i], SUPPORTED_MODES) == false) {
				throw exceptionIRC(ERR_UNKNOWNMODE, ERRDESC_UNKNOWNMODE, std::string(1, modesGiven[i]));
			}
		} catch (const exceptionIRC &e) {
			std::string	errorMessage = e.buildErrorMessage(users[socketFd]->getNickname());
			users[socketFd]->enqueueMessage(errorMessage);
			logCommandToUser(errorMessage, *users[socketFd]);
			continue;
		}
		// 3.
		modeAndParameter.first = std::string(1, modesGiven[i]);
		try {
			if (addMode && isIn(modesGiven[i], PLUS_MODES_EXPECTING_ARGUMENT)) {
				if (parameterIndex >= (int)argv.size()) {
					throw exceptionIRC(ERR_NEEDMOREPARAMS, ERRDESC_NEEDMOREPARAMS, "MODE");
				}
				modeAndParameter.second = argv[parameterIndex];
				parameterIndex++;
			} else if (!addMode && isIn(modesGiven[i], MINUS_MODES_EXPECTING_ARGUMENT)) {
				if (parameterIndex >= (int)argv.size()) {
					throw exceptionIRC(ERR_NEEDMOREPARAMS, ERRDESC_NEEDMOREPARAMS, "MODE");
				}
				modeAndParameter.second = argv[parameterIndex];
				parameterIndex++;
			} else {
				modeAndParameter.second = "";
			}
		} catch (const exceptionIRC &e) {
			std::string	errorMessage = e.buildErrorMessage(users[socketFd]->getNickname());
			users[socketFd]->enqueueMessage(errorMessage);
			logCommandToUser(errorMessage, *users[socketFd]);
			continue;
		}
		// 4.
		result.push(modeAndParameter);
		modeAndParameter.first.clear();
		modeAndParameter.second.clear();
	}
	return result;
}