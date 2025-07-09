#include "./Channel.hpp"
#include "../includes/ft_irc.hpp"

/*
	1. Check if requester is an operator
	2. On removal
		a. check if channel has a user limit set if not, send empty line
		b. remove user limit if limit is set
	3. On addition
		a. check if user limit is given, if not, throw ERR_NEEDMOREPARAMS
		b. if limit given is less then 0, send empty line -> ERROR HAPPENS WHEN YOU TRY TO SET LIMIT TO -10 -> it happens before getting into the function !!!!!!!!!!!!!!!!!
		c. if limit given matches the current limit, send empty line
		d. set limit
*/
void modeL(bool addMode, Channel *channel, User *requester, std::string limitGiven, const std::vector<Connection *> &channelUsers) {

	// 1.
	if (!MembershipRelation::isUserAnOperator(requester, channelUsers))
		throw exceptionIRC(ERR_CHANOPRIVSNEEDED, ERRDESC_CHANOPRIVSNEEDED, channel->getName());

	// 2.
	if (!addMode) {
		// a.
		if (channel->getUserLimit() == -1) {
			throw exceptionIRC(ERR_EMPTYLINE, ERRDESC_EMPTYLINE);
		}
		// b.
		channel->setUserLimit(-1);
	}
	// 3.
	if (addMode) {
		// a.
		if (limitGiven.empty())
			throw exceptionIRC(ERR_NEEDMOREPARAMS, ERRDESC_NEEDMOREPARAMS, "MODE");

		// b.
		int limit = ft_atoi(limitGiven);
		if (limit < 0) {
			std::string errMsg = channel->getName() + " l " + limitGiven;
			throw exceptionIRC(ERR_INVLIMITMODE, ERRDESC_INVLIMITMODE, errMsg);
		}
		// c.
		if (channel->getUserLimit() == limit) {
			throw exceptionIRC(ERR_EMPTYLINE, ERRDESC_EMPTYLINE);
		}
		// d.
		channel->setUserLimit(limit);
	}
}