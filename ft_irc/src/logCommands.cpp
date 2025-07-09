#include "../includes/ft_irc.hpp"
#include <ctime>

// Returns the timestamp in the format specified in the Common Log Format page on Wikipedia
// Buffer should have 32 bytes allocated
static void	getTimestamp(char *buffer) {
	std::time_t now = std::time(0);
	std::tm *gmt = std::gmtime(&now);
	std::strftime(buffer, 32, "%d/%b/%Y:%H:%M:%S %z", gmt);
}

void	logCommandToUser(const std::string &command, const User &receiver) {
	char	timestamp[32];
	std::string	token = command;
	std::size_t	endPos;
	std::ostream	&output = std::cout;

	getTimestamp(timestamp);
	while (true) {
		endPos = token.find('\n');
		if (endPos == std::string::npos)
			break;
		output << "127.0.0.1 -> ";
		output << "fd:" << receiver.getUserSocketFd() << " ";
		if (receiver.getNickname().empty())
			output << '-';
		else
			output << receiver.getNickname();
		output << " [" << timestamp << "] ";
		try
		{
			if (token.at(endPos - 1) == '\r')
				output << "\"" << token.substr(0, endPos - 1) << "\"";
			else
				output << "\"" << token.substr(0, endPos) << "\"";
		}
		catch (const std::out_of_range &e) {
			output << "\"" << token.substr(0, endPos) << "\"";
		}
		output << std::endl;
		token = token.substr(endPos + 1);
	}
}

void	logCommandToServer(const std::string &command, const User &sender) {
	char	timestamp[32];
	std::string	token = command;
	std::size_t	endPos;
	std::ostream &output = std::cout;

	getTimestamp(timestamp);
	while (true) {
		endPos = token.find('\n');
		if (endPos == std::string::npos)
			break;
		output << "fd:" << sender.getUserSocketFd() << " ";
		if (sender.getNickname().empty())
			output << '-';
		else
			output << sender.getNickname();
		output << " -> 127.0.0.1";
		output << " [" << timestamp << "] ";
		try
		{
			if (token.at(endPos - 1) == '\r')
				output << "\"" << token.substr(0, endPos - 1) << "\"";
			else
				output << "\"" << token.substr(0, endPos) << "\"";
		}
		catch (const std::out_of_range &e) {
			output << "\"" << token.substr(0, endPos) << "\"";
		}
		output << std::endl;
		token = token.substr(endPos + 1);
	}
}
