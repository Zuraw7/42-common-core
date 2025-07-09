#include "../includes/ft_irc.hpp"

void	sendToUsers(const User &sender, const std::vector<Connection *> &channelUsers, const std::string &message) {
	(void)sender;
	for (std::vector<Connection *>::const_iterator it = channelUsers.begin(); it != channelUsers.end(); it++) {
		(*it)->user->enqueueMessage(message);
		logCommandToUser(message, *(*it)->user);
	}
}

void	sendToUserChannels(const User &sender, MembershipRelation &membership, const std::string &message) {
	for (std::vector<Connection *>::const_iterator it = membership.getUserChannels(&sender).begin(); it != membership.getUserChannels(&sender).end(); it++) {
		for (std::vector<Connection *>::const_iterator uIt = membership.getChannelUsers((*it)->channel).begin(); uIt != membership.getChannelUsers((*it)->channel).end(); uIt++) {
			(*uIt)->user->enqueueMessage(message);
			logCommandToUser(message, *(*uIt)->user);
		}
	}
}

void	handleCap(command &argv, User &currentUser) {
	std::string	response;

	if (argv.size() < 2)
		throw exceptionIRC(ERR_NEEDMOREPARAMS, ERRDESC_NEEDMOREPARAMS, "CAP");
	if (currentUser.getNegotiationStatus())
		throw exceptionIRC(ERR_ALREADYREGISTRED, ERRDESC_ALREADYREGISTRED);
	if (argv.at(1) == "LS") {
		response = "CAP * LS :\r\n";
	} else if (argv.at(1) == "REQ") {
		if (argv.size() < 3)
			throw exceptionIRC(ERR_NEEDMOREPARAMS, ERRDESC_NEEDMOREPARAMS, "CAP");
		response = "CAP * NAK " + argv.at(2);
	} else if (argv.at(1) == "END") {
		currentUser.setNegotiationStatus(true);
	} else {
		return ;
	}
	logCommandToUser(response, currentUser);
	currentUser.enqueueMessage(response);
}

void	handleNick(command &argv, std::map<int, User *> &users, int socketFd, MembershipRelation &membership) {
	if (users[socketFd]->getCorrectServerPassword() == false)
		throw exceptionIRC(ERR_EMPTYLINE, ERRDESC_EMPTYLINE);
	if (argv.size() == 1)
		throw exceptionIRC(ERR_NONICKNAMEGIVEN, ERRDESC_NONICKNAMEGIVEN);
	std::string	oldNickname(users[socketFd]->getNickname());
	users[socketFd]->setNickname(argv.at(1), users);
	if (users[socketFd]->getAuthenticationStatus()) {
		sendToUserChannels(*users[socketFd], membership, buildCommand(std::string(":").append(oldNickname), "NICK", users[socketFd]->getNickname()));
	}
	if (users[socketFd]->getUsername() != "")
		users[socketFd]->setAuthenticationStatus(true);
}

/*
	The second and third argument (hostname and servername) is not taken into account
	because we are only implementing local connections
*/
void	handleUser(command &argv, User &currentUser) {
	if (currentUser.getCorrectServerPassword() == false)
		throw exceptionIRC(ERR_EMPTYLINE, ERRDESC_EMPTYLINE);
	if (argv.size() < 5)
		throw exceptionIRC(ERR_NEEDMOREPARAMS, ERRDESC_NEEDMOREPARAMS, "USER");
	if (currentUser.getUsername() != "")
		throw exceptionIRC(ERR_ALREADYREGISTRED, ERRDESC_ALREADYREGISTRED);
	currentUser.setUsername(argv.at(1));
	currentUser.setRealname(argv.at(4));
	if (currentUser.getNickname() != "")
		currentUser.setAuthenticationStatus(true);
}

void	handlePing(command &argv, User &user) {
	std::string	response("PONG");
	if (!user.getAuthenticationStatus())
		throw exceptionIRC(ERR_NOTREGISTERED, ERRDESC_NOTREGISTERED);
	if (argv.size() > 1) {
		response.append(" ");
		response.append(argv.at(1));
	}
	response.append("\r\n");
	logCommandToUser(response, user);
	user.enqueueMessage(response);
}

void	handlePrivmsg(command &argv, std::map<int, User *> &users, int socketFd, MembershipRelation &membership) {
	User	*recipient = NULL;
	std::string response;
	if (!users[socketFd]->getAuthenticationStatus())
		throw exceptionIRC(ERR_NOTREGISTERED, ERRDESC_NOTREGISTERED);
	if (argv.size() == 1 || argv.at(1).empty())
		throw exceptionIRC(ERR_NORECIPIENT, ERRDESC_NORECIPIENT, argv.at(0));
	if (argv.size() == 2 || argv.at(2).empty())
		throw exceptionIRC(ERR_NOTEXTTOSEND, ERRDESC_NOTEXTTOSEND);
	command channelNames = split(argv.at(1), ',');
	for (command::iterator it = channelNames.begin(); it != channelNames.end(); it++) {
		if (it->at(0) != '#' && it->at(0) != '&') {
			recipient = User::getUserByNickname(users, *it);
			if (recipient == NULL)
				throw exceptionIRC(ERR_NOSUCHNICK, ERRDESC_NOSUCHNICK, *it);
			response = buildDeliverMessage(users[socketFd]->getSenderInfo(), recipient->getNickname(), argv.at(2));
			logCommandToUser(response, *users[socketFd]);
			recipient->enqueueMessage(response);
		} else {
			Channel	*channel = membership.getChannelByName(*it);
			if (channel == NULL)
				throw exceptionIRC(ERR_NOSUCHNICK, ERRDESC_NOSUCHNICK, *it);
			else if (!MembershipRelation::isUserInChannel(users[socketFd], membership.getChannelUsers(channel)))
				throw exceptionIRC(ERR_CANNOTSENDTOCHAN, ERRDESC_CANNOTSENDTOCHAN, *it);
			response = buildDeliverMessage(users[socketFd]->getSenderInfo(), channel->getName(), argv.at(2));
			sendToUsers(*users[socketFd], membership.getChannelUsers(channel), response);
		}
	}
}

/*
	1. Check if there is enough parameters
	2. Parse channel names and passwords
		- names and passwords are separated by commas and space
		- i.e. #42,#24,#23 42,24,23
	3. Check if channel already exists
		- check if name is correct, prefix is # or &
		- if no -> create new channel
		- if yes -> check if user is already in the channel
		- add user to the channel if password is correct or if there is no password
			- send RPL_TOPIC
	4. Send JOIN message to the user
	5. Send JOIN message to all other users in the channel
	6. Send RPL_NAMREPLY and RPL_ENDOFNAMES to the user, informs user about all users in the channel
*/
void handleJoin(command &argv, std::map<int, User *> &users, int socketFd, MembershipRelation &membership) {
	// 1.
	if (!users[socketFd]->getAuthenticationStatus())
		throw exceptionIRC(ERR_NOTREGISTERED, ERRDESC_NOTREGISTERED);
	if (argv.size() < 2) 
		throw exceptionIRC(ERR_NEEDMOREPARAMS, ERRDESC_NEEDMOREPARAMS, "JOIN");
	
	// 2.
	std::string names;
	std::string passwords;
	if (argv.size() == 3) {
		names = argv.at(1);
		passwords = argv.at(2);
	} else if (argv.size() == 2) {
		names = argv.at(1);
		passwords = "";
	}

	std::vector<std::string> channelNames = split(names, ',');
	std::vector<std::string> channelPasswords = split(passwords, ',');

	// 3.
	for (size_t i = 0; i < channelNames.size(); i++) {
		try {
			checkName(channelNames[i]);
		} catch (const exceptionIRC &e) {
			std::string errorMessage = e.buildErrorMessage(users[socketFd]->getNickname());
			users[socketFd]->enqueueMessage(errorMessage);
			logCommandToUser(errorMessage, *users[socketFd]);
			continue;
		}

		std::string channelName = channelNames[i];
		std::string channelPassword;
		if (i < channelPasswords.size()) {
			channelPassword = channelPasswords[i];
		} else {
			channelPassword = "";
		}

		Channel	*channel = membership.getChannelByName(channelName);
		try {
			if (channel == NULL) {
				Channel *channel = new Channel(channelName, channelPassword);
				membership.addNewChannel(channel, users[socketFd]);
			} else if (channel->getPassword() != "" && channel->getPassword() != channelPassword) {
				throw exceptionIRC(ERR_BADCHANNELKEY, ERRDESC_BADCHANNELKEY, channel->getName());
			} else {
				membership.addUserToChannel(users[socketFd], channel, false);
				if (channel->getTopic() != "")
					sendRPL(RPL_TOPIC, users[socketFd], channel->getName() + " :" + channel->getTopic());
			}
		} catch (const exceptionIRC &e) {
			std::string errorMessage = e.buildErrorMessage(users[socketFd]->getNickname());
			users[socketFd]->enqueueMessage(errorMessage);
			logCommandToUser(errorMessage, *users[socketFd]);
			continue;
		}
		
		// 4. && 5.
		std::string joinMsg = buildCommand(users[socketFd]->getSenderInfo(), "JOIN", channelName);
		users[socketFd]->enqueueMessage(joinMsg);
		logCommandToUser(joinMsg, *users[socketFd]);
		std::vector<Connection *>	&connections = membership.getConnectionsByChannelName(channelName);
		sendToUsers(*users[socketFd], connections, joinMsg);

		// 6.
		connections.at(0)->channel->sendUserList(users[socketFd], connections);
	}
}

/*
	Works only for channels
	1. Check if user gave enough parameters
	2. Check if channel exists
	3. Check if user gave "o" parameter
	4. Get channel users
	5. Send response to user
*/
void handleWho(command &argv, User &user, MembershipRelation &membership) {
	if (!user.getAuthenticationStatus())
		throw exceptionIRC(ERR_NOTREGISTERED, ERRDESC_NOTREGISTERED);

	// 1.
	if (argv.size() < 2)
		throw exceptionIRC(ERR_NEEDMOREPARAMS, ERRDESC_NEEDMOREPARAMS, "WHO");
	
	// 2.
	std::string channelName = argv.at(1);
	Channel *channel = membership.getChannelByName(channelName);
	if (channel == NULL) {
		sendRPL(RPL_ENDOFWHO, &user, channelName + " :End of /WHO list");
		return;
	}

	// 3.
	bool showOpsOnly = false;
	if (argv.size() > 2 && argv.at(2) == "o") {
		showOpsOnly = true;
	}
	
	// 4.
	std::vector<Connection *> channelUsers = membership.getChannelUsers(channel);
	std::string listOfUsers;
	for (std::vector<Connection *>::iterator it = channelUsers.begin(); it != channelUsers.end(); it++) {
		if (showOpsOnly && !(*it)->isOperator)
			continue;
		if ((*it)->isOperator)
			listOfUsers += "@";
		listOfUsers += (*it)->user->getNickname() + " ";
	}

	// 5.
	sendRPL(RPL_WHOREPLY, &user, channelName + " :" + listOfUsers);
	sendRPL(RPL_ENDOFWHO, &user, channelName + " :End of /WHO list");
}

void handlePassword(command &argv, User &user, const std::string &serverPassword) {
	if (serverPassword.empty())
		user.setCorrectServerPassword(true);
	if (user.getAuthenticationStatus())
		throw exceptionIRC(ERR_ALREADYREGISTRED, ERRDESC_ALREADYREGISTRED);
	if (argv.size() < 2)
		throw exceptionIRC(ERR_NEEDMOREPARAMS, ERRDESC_NEEDMOREPARAMS, "PASS");
	if (user.getCorrectServerPassword())
		return ;
	if (argv.at(1) != serverPassword)
		throw exceptionIRC(ERR_PASSWDMISMATCH, ERRDESC_PASSWDMISMATCH);
	user.setCorrectServerPassword(true);
}
