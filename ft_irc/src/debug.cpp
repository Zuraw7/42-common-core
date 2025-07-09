#include "ft_irc.hpp"

void	debugPrint(command &argv, std::map<int, User *> &users, int socketFd, MembershipRelation &membership) {
	(void)users;
	(void)socketFd;
	if (argv.size() < 2) 
		throw exceptionIRC(ERR_NEEDMOREPARAMS, ERRDESC_NEEDMOREPARAMS, "PRINT");
	if (argv.at(1) == "MEMBERSHIP") {
		std::cout << "--- PRINTING MEMBERSHIP ---\nUserChannels:\n";
		for (UserConnections::const_iterator it = membership.getUserChannels().begin(); it != membership.getUserChannels().end(); it++) {
			std::cout << "User: " << it->first->getNickname() << " is in channels: ";
			for (std::vector<Connection *>::const_iterator itt = it->second.begin(); itt != it->second.end(); itt++) {
				if ((*itt)->isInvited)
					std::cout << "[INV]";
				else if ((*itt)->isOperator)
					std::cout << "[OP]";
				std::cout << (*itt)->channel->getName();
				std::cout << " ";
			}
			std::cout << std::endl;
		}
		std::cout << "ChannelUsers:\n";
		for (ChannelConnections::const_iterator it = membership.getChannelUsers().begin(); it != membership.getChannelUsers().end(); it++) {
			std::cout << "Channel: " << it->first->getName() << " has users: ";
			for (std::vector<Connection *>::const_iterator itt = it->second.begin(); itt != it->second.end(); itt++) {
				if ((*itt)->isInvited)
					std::cout << "[INV]";
				else if ((*itt)->isOperator)
					std::cout << "[OP]";
				std::cout << (*itt)->user->getNickname();
				std::cout << " ";
			}
			std::cout << std::endl;
		}
	}
	std::cout << "--- END OF PRINT ---\n";
}