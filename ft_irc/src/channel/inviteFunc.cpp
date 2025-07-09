#include "./Channel.hpp"
#include "../includes/ft_irc.hpp"

/*
	1. Check if there is enough parameters
	2. Find user to invite
	3. Find given channel
	4. Check if inviter is a member of the channel
	5. Check if invited user is already in the channel
	6. Check if channel is invite-only
		a. if so check if inviter is an operator
	7. Invite user to channel

	ERRORS:
		ERR_NEEDMOREPARAMS
		ERR_NOSUCHNICK
		ERR_NOTONCHANNEL
		ERR_USERONCHANNEL
		ERR_CHANOPRIVSNEEDED

	REPLIES:
		RPL_INVITING
*/
void handleInvite(command &argv, std::map<int, User *> &users, int socketFd, MembershipRelation &membership)
{
	User *inviter = users[socketFd];
	if (!inviter->getAuthenticationStatus())
		throw exceptionIRC(ERR_NOTREGISTERED, ERRDESC_NOTREGISTERED);
	
	// 1.
	if (argv.size() < 3)
		throw exceptionIRC(ERR_NEEDMOREPARAMS, ERRDESC_NEEDMOREPARAMS, "INVITE");

	// 2.
	User *invitedUser = NULL;
	for (std::map<int, User *>::iterator it = users.begin(); it != users.end(); it++)
	{
		if (it->second->getNickname() == argv[1])
		{
			invitedUser = it->second;
			break;
		}
	}
	if (invitedUser == NULL)
		throw exceptionIRC(ERR_NOSUCHNICK, ERRDESC_NOSUCHNICK, argv[1]);

	// 3.
	checkName(argv[2]);
	Channel *channel = membership.getChannelByName(argv[2]);
	if (channel == NULL)
		throw exceptionIRC(ERR_NOSUCHCHANNEL, ERRDESC_NOSUCHCHANNEL, argv[2]);
	
	// 4. 
	if (MembershipRelation::isUserInChannel(inviter, membership.getChannelUsers(channel)) == false)
		throw exceptionIRC(ERR_NOTONCHANNEL, ERRDESC_NOTONCHANNEL, channel->getName());

	// 5.
	if (MembershipRelation::isUserInChannel(invitedUser, membership.getChannelUsers(channel)) == true)
		throw exceptionIRC(ERR_USERONCHANNEL, ERRDESC_USERONCHANNEL, invitedUser->getNickname() + " " + channel->getName());
	
	// 6.
	if (channel->getInvOnlyStatus() == true) {
		// a.
		if (MembershipRelation::isUserAnOperator(inviter, membership.getChannelUsers(channel)) == false)
			throw exceptionIRC(ERR_CHANOPRIVSNEEDED, ERRDESC_CHANOPRIVSNEEDED, channel->getName());
	}

	// 7.
	membership.addUserToChannel(invitedUser, channel, true);

	std::string message = buildCommand(std::string(":").append(inviter->getNickname()), "INVITE", invitedUser->getNickname() + " " + channel->getName());
	
	sendRPL(RPL_INVITING, inviter, invitedUser->getNickname() + " " + channel->getName());
	invitedUser->enqueueMessage(message);
	logCommandToUser(message, *invitedUser);
}