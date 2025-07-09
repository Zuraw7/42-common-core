#include "./Channel.hpp"
#include "../includes/ft_irc.hpp"

/*
	1. If a user attempts to make themselves an operator using the "+o" flag, the attempt should be ignored.
	2. Check if requester is an operator
	3. Check if user to use mode on is in channel
	4. Check if user is already an operator (if adding mode) or is not an operator (if removing mode)
	5. Execute the mode change
*/
void modeO(bool addMode, Channel *channel, User *requester, User *toOp, const std::vector<Connection *> &channelUsers) {
	if (requester == toOp && addMode)
		return;
	// 2.
	if (!MembershipRelation::isUserAnOperator(requester, channelUsers))
		throw exceptionIRC(ERR_CHANOPRIVSNEEDED, ERRDESC_CHANOPRIVSNEEDED, channel->getName());
	// 3.
	if (!MembershipRelation::isUserInChannel(toOp, channelUsers))
		throw exceptionIRC(ERR_NOSUCHNICK, ERRDESC_NOSUCHNICK, toOp->getNickname());
	// 4.
	if ((addMode && MembershipRelation::isUserAnOperator(toOp, channelUsers)) || (!addMode && !MembershipRelation::isUserAnOperator(toOp, channelUsers)))
	{
		throw exceptionIRC(ERR_EMPTYLINE, ERRDESC_EMPTYLINE);
	}
	// 5.
	if (addMode) {
		MembershipRelation::memberToOperator(toOp, channelUsers);
	} else {
		MembershipRelation::operatorToMember(toOp, channelUsers);
	}
}