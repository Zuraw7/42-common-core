#include "./Channel.hpp"
#include "../includes/ft_irc.hpp"

/*
	1. Check if there is enough parameters if not ERR_NEEDMOREPARAMS
	2. Check if channel exist and is user in the channel
	3. If there is only channel name, send RPL_NOTOPIC or RPL_TOPIC
	4. If there is a topic given
		a. Check if channel is settable by op only if so check if user is op
		b. Check if given topic is not the same as current topic, if so throw ERR_EMPTYLINE
		c. Set topic
		d. Send info that topic was changed by requester

	ERRORS:
		ERR_NEEDMOREPARAMS
		ERR_NOTONCHANNEL
		ERR_CHANOPRIVSNEEDED

	REPLIES:
		RPL_NOTOPIC
		RPL_TOPIC
*/
void handleTopic (command &argv, std::map<int, User *> &users, int socketFd, MembershipRelation &membership) {
	if (!users[socketFd]->getAuthenticationStatus())
		throw exceptionIRC(ERR_NOTREGISTERED, ERRDESC_NOTREGISTERED);
	
	// 1.
	if (argv.size() < 2)
		throw exceptionIRC(ERR_NEEDMOREPARAMS, ERRDESC_NEEDMOREPARAMS, "TOPIC");
	
	// 2.
	checkName(argv.at(1));
	Channel *channel = membership.getChannelByName(argv.at(1));
	if (channel == NULL)
		throw exceptionIRC(ERR_NOSUCHCHANNEL, ERRDESC_NOSUCHCHANNEL, argv.at(1));
	if  (MembershipRelation::isUserInChannel(users[socketFd], membership.getChannelUsers(channel)) == false)
		throw exceptionIRC(ERR_NOTONCHANNEL, ERRDESC_NOTONCHANNEL, argv.at(1));
	
	// 3.
	if (argv.size() == 2) {
		if (channel->getTopic().empty())
			sendRPL(RPL_NOTOPIC, users[socketFd], channel->getName() + " :No topic is set");
		else
			sendRPL(RPL_TOPIC, users[socketFd], channel->getName() + " :" + channel->getTopic());
	}
	// 4.
	else {
		// a.
		if (channel->getTopicSettableByOpOnly() == true) {
			if (MembershipRelation::isUserAnOperator(users[socketFd], membership.getChannelUsers(channel)) == false)
				throw exceptionIRC(ERR_CHANOPRIVSNEEDED, ERRDESC_CHANOPRIVSNEEDED, argv.at(1));
		}
		// b.
		if (argv[2] == channel->getTopic()) {
			throw exceptionIRC(ERR_EMPTYLINE, ERRDESC_EMPTYLINE);
		}
		// c.
		std::string newTopic = argv[2];
		if (newTopic[0] == ':')
			newTopic = newTopic.substr(1);
		channel->setTopic(newTopic);
		// d.
		std::string message = buildCommand(users[socketFd]->getSenderInfo(), "TOPIC", channel->getName() + " :" + channel->getTopic());
		sendToUsers(*users[socketFd], membership.getChannelUsers(channel), message);
	}
}
