#include "ft_irc.hpp"
#include <sstream>

// Build a command to be sent to the client
// :<sender> <command> <parameters>
std::string	buildCommand(const std::string &senderUserInfo, const char *command, const std::string &parameters)
{
	std::ostringstream oss;
	oss << senderUserInfo << " ";
	oss << command << " ";
	oss << parameters << "\r\n";

	return oss.str();
}

// For sending the message to a user the recipientName is the userNickname, for channels its the channelName, it has to have # in front
// :<sender> PRIVMSG <recipient> :<message>
std::string	buildDeliverMessage(const std::string &senderUserInfo, const std::string &recipientName, const std::string &message)
{
	std::ostringstream oss;
	oss << senderUserInfo << " PRIVMSG ";
	oss << recipientName << " ";
	oss << message << "\r\n";

	return oss.str();
}

#define WELCOME_MESSAGE_LINES 4 // for now a max of 9
#define RPL_WELCOME ":Hello and welcome %s"
#define RPL_YOURHOST ":Your host is %s, running version delux"
#define RPL_CREATED ":This server was created at whatever time it was created, who am I to know?"
#define RPL_MYINFO "%s 0.1 o o"
// :<sender (the server domain)> <message num> <recipient> :<message>
std::string	buildWelcomeMessage(const std::string &recipientNickname)
{
	char	messages[WELCOME_MESSAGE_LINES][100] = {RPL_WELCOME, RPL_YOURHOST, RPL_CREATED, RPL_MYINFO};
	std::ostringstream	oss;
	std::string			message;
	std::size_t			pos = 0;
	for (unsigned short i = 1; i <= WELCOME_MESSAGE_LINES; i++) {
		oss << ":" << SERVER_HOSTNAME << " 00" << i;
		oss << " " << recipientNickname << " ";
		message = std::string(messages[i - 1]);
		pos = message.find("%s");
		switch (i)
		{
		case 1:
			if (pos != message.npos) {
				oss << message.substr(0, pos);
				oss << recipientNickname;
				if (pos + 2 < message.length())
					oss << message.substr(pos + 2);
			}
			break;
		case 2:
			// falls through
		case 4:
			if (pos != message.npos) {
				oss << message.substr(0, pos);
				oss << SERVER_HOSTNAME;
				if (pos + 2 < message.length())
					oss << message.substr(pos + 2);
			}
			break;
		default:
			oss << message;
			break;
		}
		oss << "\r\n";
	}
	

	return oss.str();
}

#define RPL_MOTD_MESSAGE "Hello, this is the greatest IRC server in existance!"
#define MOTD_LINES 3
std::string	buildMessageOfTheDay(const std::string &recipientNickname)
{
	char	messages[MOTD_LINES][100] = {RPLDESC_MOTDSTART, RPLDESC_MOTD, RPLDESC_ENDOFMOTD};
	unsigned short	codes[MOTD_LINES] = {RPL_MOTDSTART, RPL_MOTD, RPL_ENDOFMOTD};
	std::ostringstream	oss;
	std::string			message;
	std::size_t			pos = 0;
	for (unsigned short i = 1; i <= MOTD_LINES; i++) {
		oss << ":" << SERVER_HOSTNAME;
		oss << " " << codes[i - 1] << " ";
		oss << recipientNickname << " ";
		message = std::string(messages[i - 1]);
		pos = message.find("%s");
		switch (i)
		{
		case 1:
			if (pos != message.npos) {
				oss << message.substr(0, pos);
				oss << SERVER_HOSTNAME;
				if (pos + 2 < message.length())
					oss << message.substr(pos + 2);
			}
			break;
		case 2:
			if (pos != message.npos) {
				oss << message.substr(0, pos);
				oss << RPL_MOTD_MESSAGE;
				if (pos + 2 < message.length())
					oss << message.substr(pos + 2);
			}
			break;
		default:
			oss << message;
			break;
		}
		oss << "\r\n";
	}
	

	return oss.str();
}