#include "./Channel.hpp"
#include "../includes/ft_irc.hpp"

void checkNames(std::vector<std::string> &givenChannels, User *kicker);
std::vector<Channel *> checkChannels(std::vector<std::string> &givenChannels, MembershipRelation &membership, User *kicker);
void checkKicker(std::vector<Channel *> &channels, User *kicker, MembershipRelation &membership);
User *findUser(const std::string &nickname, std::vector<Connection *> &channelUsers, std::map<int, User *> &users);
void kickUser(User *kicker, User *userToKick, std::vector<Connection *> &channelUsers, const std::string &reason, MembershipRelation &membership);

/*
	1. Check if there is enough parameters
	2. Check if channels names are valid
	3. Create a list of channels to kick from and check if they exist
	4. Check if user is in the channels and if he is a channel operator if no, erease channel from the list
	5. 
		a. get current channel user list, if empty go to next channel
		b. check if user to kick is in the channel, if not, send error message and go to next user
		d. if user to kick is in the channel, kick him
*/
void handleKick(command &argv, std::map<int, User *> &users, int socketFd, MembershipRelation &membership) {
	if (!users[socketFd]->getAuthenticationStatus())
		throw exceptionIRC(ERR_NOTREGISTERED, ERRDESC_NOTREGISTERED);
	// 1.
	if (argv.size() < 3)
		throw exceptionIRC(ERR_NEEDMOREPARAMS, ERRDESC_NEEDMOREPARAMS, "KICK");

	// 2.
	std::vector<std::string> givenChannels = split(argv.at(1), ',');
	checkNames(givenChannels, users[socketFd]);

	// 3.
	std::vector<Channel *> channels = checkChannels(givenChannels, membership, users[socketFd]);
	
	// 4.
	checkKicker(channels, users[socketFd], membership);

	std::string reason;
	if (argv.size() == 3)
		reason = "";
	else
		reason = " :" + argv.at(3);

	// 5.
	std::vector<std::string> usersToKick = split(argv.at(2), ',');

	// for each channel
	for (std::vector<Channel *>::iterator it = channels.begin(); it != channels.end(); it++) {

		// for each user
		for (std::vector<std::string>::iterator i = usersToKick.begin(); i != usersToKick.end(); i++) {

			// a.
			std::vector<Connection *> channelUsers = membership.getChannelUsers(*it);
			if (channelUsers.empty())
				break;

			// b.
			User *userToKick = findUser(*i, channelUsers, users);
			try {
				if (userToKick == NULL)
					throw exceptionIRC(ERR_USERNOTINCHANNEL, ERRDESC_USERNOTINCHANNEL, *i + " " + channelUsers.at(0)->channel->getName());
			} catch (const exceptionIRC &e) {
				std::string errorMessage = e.buildErrorMessage(users[socketFd]->getNickname());
				users[socketFd]->enqueueMessage(errorMessage);
				logCommandToUser(errorMessage, *users[socketFd]);
				continue;
			}

			// d.
			kickUser(users[socketFd], userToKick, channelUsers, reason, membership);
		}
	}
}

void checkNames(std::vector<std::string> &givenChannels, User *kicker) {
	for (std::vector<std::string>::iterator it = givenChannels.begin(); it != givenChannels.end(); it++) {
		try {
			checkName(*it);
		} catch (const exceptionIRC &e) {
			std::string errorMessage = e.buildErrorMessage(kicker->getNickname());
			kicker->enqueueMessage(errorMessage);
			logCommandToUser(errorMessage, *kicker);
		}
	}
}

std::vector<Channel *> checkChannels(std::vector<std::string> &givenChannels, MembershipRelation &membership, User *kicker) {
	std::vector<Channel *> channels;

	for (std::vector<std::string>::iterator it = givenChannels.begin(); it != givenChannels.end(); it++) {
		try {
			Channel *channel = membership.getChannelByName(*it);
			if (channel == NULL)
				throw exceptionIRC(ERR_NOSUCHCHANNEL, ERRDESC_NOSUCHCHANNEL, *it);
			channels.push_back(channel);
		} catch (const exceptionIRC &e) {
			std::string errorMessage = e.buildErrorMessage(kicker->getNickname());
			kicker->enqueueMessage(errorMessage);
			logCommandToUser(errorMessage, *kicker);
			continue;
		}
	}
	return channels;
}

void checkKicker(std::vector<Channel *> &channels, User *kicker, MembershipRelation &membership) {
	for (std::vector<Channel *>::iterator it = channels.begin(); it != channels.end(); it++) {
		try {
			if (!MembershipRelation::isUserInChannel(kicker, membership.getChannelUsers(*it)))
				throw exceptionIRC(ERR_NOTONCHANNEL, ERRDESC_NOTONCHANNEL, (*it)->getName());
			if (!MembershipRelation::isUserAnOperator(kicker, membership.getChannelUsers(*it)))
				throw exceptionIRC(ERR_CHANOPRIVSNEEDED, ERRDESC_CHANOPRIVSNEEDED, (*it)->getName());
		} catch (const exceptionIRC &e) {
			std::string errorMessage = e.buildErrorMessage(kicker->getNickname());
			kicker->enqueueMessage(errorMessage);
			logCommandToUser(errorMessage, *kicker);
			channels.erase(it);
			it--;
			continue;
		}
	}
}

User *findUser(const std::string &nickname, std::vector<Connection *> &channelUsers, std::map<int, User *> &users) {
	for (std::vector<Connection *>::const_iterator it = channelUsers.begin(); it != channelUsers.end(); it++) {
		if ((*it)->user->getNickname() == nickname) {
			return users[(*it)->user->getUserSocketFd()];
		}
	}
	return NULL;
}

void kickUser(User *kicker, User *userToKick, std::vector<Connection *> &channelUsers, const std::string &reason, MembershipRelation &membership) {
	std::string message = buildCommand(std::string(":").append(kicker->getNickname()), "KICK", channelUsers.at(0)->channel->getName() + " " + userToKick->getNickname() + reason);

	sendToUsers(*kicker, channelUsers, message);	
	membership.removeUserFromChannel(userToKick, channelUsers.at(0)->channel);
}
