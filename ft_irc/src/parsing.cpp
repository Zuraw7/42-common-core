#include "ft_irc.hpp"
#include "utils.hpp"

#define IGNORE_SPACES ':'
#define COMMAND_DELIM ' '
#define COMMAND_DELIM_LENGTH 1
#define LINE_DELIM "\r\n"
#define LINE_DELIM_LENGTH 2
#define LINE_DELIM_FALLBACK '\n'

command	splitCommand(std::string oneCommand) {
	std::size_t	pos = 0;
	std::size_t	ignoreSpacesPos;
	command		argv;

	ignoreSpacesPos = oneCommand.find(IGNORE_SPACES);
	pos = oneCommand.find(COMMAND_DELIM);
	while (pos != oneCommand.npos)
	{
		if (ignoreSpacesPos != oneCommand.npos && pos > ignoreSpacesPos) {
			argv.push_back(oneCommand);
			return argv;
		}
		argv.push_back(oneCommand.substr(0, pos));
		oneCommand.erase(0, pos + COMMAND_DELIM_LENGTH);
		pos = oneCommand.find(COMMAND_DELIM);
		ignoreSpacesPos = oneCommand.find(IGNORE_SPACES);
	}
	if (!oneCommand.empty())
		argv.push_back(oneCommand.substr(0, pos));
	return argv;
}

commands	getSplittedCommands(std::string message) {
	std::size_t	pos = 0;
	std::string	oneCommand;
	commands	commandVector;

	if (message.empty() || message.at(0) == '\n' || message.at(0) == '\r')
		return commandVector;
	pos = message.find("\r\n");
	while (pos != message.npos) {
		oneCommand = message.substr(0, pos);
		message.erase(0, pos + LINE_DELIM_LENGTH);
		commandVector.push_back(splitCommand(oneCommand));
		pos = message.find(LINE_DELIM);
		if (pos == message.npos)
			pos = message.find(LINE_DELIM_FALLBACK);
	}
	if (!message.empty()) {
		oneCommand = message.substr(0, pos);
		pos = oneCommand.find(LINE_DELIM);
		if (pos != oneCommand.npos)
			oneCommand.at(pos) = '\0';
		if (pos != oneCommand.npos)
			pos = oneCommand.find(LINE_DELIM_FALLBACK);
		if (pos != oneCommand.npos)
			oneCommand.at(pos) = '\0';
		commandVector.push_back(splitCommand(oneCommand));
	}
	return commandVector;
}

static enum commandName	getCommand(const std::string& currentCommand, const std::map<const std::string, enum commandName> commandNames) {
	enum commandName	result;

	try {
		result = commandNames.at(currentCommand);
	}
	catch (const std::out_of_range& e) {
		throw exceptionIRC(ERR_UNKNOWNCOMMAND, ERRDESC_UNKNOWNCOMMAND, currentCommand);
	}
	return result;
}

void	parseMessage(const std::map<const std::string, enum commandName> commandNames, std::map<int, User *> &users, int socketFd, MembershipRelation &membership, const std::string &serverPassword, std::set<int> &fdsToRemove) {
	commands commandVector = getSplittedCommands(users[socketFd]->getMessage());
	while (!commandVector.empty()) {
		commands::iterator	it = commandVector.begin();
		if (it->size() < 1) {
			commandVector.erase(it);
			continue;
		}
		try
		{
			enum commandName	currentCommand = getCommand(it->at(0), commandNames);
			switch (currentCommand) {
				case CAP:
					handleCap(*it, *users[socketFd]);
					break;
				case PASS:
					handlePassword(*it, *users[socketFd], serverPassword);
					break;
				case NICK:
					handleNick(*it, users, socketFd, membership);
					break;
				case USER:
					handleUser(*it, *users[socketFd]);
					break;
				case PING:
					handlePing(*it, *users[socketFd]);
					break;
				case QUIT:
					fdsToRemove.insert(socketFd);
					break;
				case PRIVMSG:
					handlePrivmsg(*it, users, socketFd, membership);
					break;
				case JOIN:
					handleJoin(*it, users, socketFd, membership);
					break;
				case KICK:
					handleKick(*it, users, socketFd, membership);
					break;
				case INVITE:
					handleInvite(*it, users, socketFd, membership);
					break;
				case TOPIC:
					handleTopic(*it, users, socketFd, membership);
					break;
				case MODE:
					handleMode(*it, users, socketFd, membership);
					break;
				case WHO:
					handleWho(*it, *users[socketFd], membership);
					break;
				case PRINT:
					if (DEBUG_MODE)
						debugPrint(*it, users, socketFd, membership);
					break;
				default:
					throw exceptionIRC(ERR_UNKNOWNCOMMAND, ERRDESC_UNKNOWNCOMMAND, it->at(0));
					break;
			}
		}
		catch(const exceptionIRC& e)
		{
			std::string	errorMessage = e.buildErrorMessage(users[socketFd]->getNickname());
			users[socketFd]->enqueueMessage(errorMessage);
			logCommandToUser(errorMessage, *users[socketFd]);
		}
		catch(const std::out_of_range& e)
		{
			//invalid syntax but unhandled!!!
			std::cerr << "WARNING!!! this is not supposed to happen!!, OUT OF RANGE " << e.what() << '\n';
		}
		catch(const std::bad_alloc& e)
		{
			continue;
		}
		catch(const std::exception& e)
		{
			std::cerr << "WARNING!!! this is not supposed to happen!!, EXCEPTION" << e.what() << '\n';
		}
		commandVector.erase(it);
	}
}