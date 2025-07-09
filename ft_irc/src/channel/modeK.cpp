#include "./Channel.hpp"
#include "../includes/ft_irc.hpp"

/*
	1. Check if requester is an operator
	2. Check if user gave password
	3. If trying to set password, check if channel already has a password
	4. If trying to remove password, check if password matches the current one
		- if it doesn't, throw ERR_KEYSET
		- if it does, remove the password
	5. If user tries to set password, and channel password is empty, set the password
*/
void modeK(bool addMode, Channel *channel, const std::string &password, User *requester, const std::vector<Connection *> &channelUsers) {
	// 1.
	if (!MembershipRelation::isUserAnOperator(requester, channelUsers))
		throw exceptionIRC(ERR_CHANOPRIVSNEEDED, ERRDESC_CHANOPRIVSNEEDED, channel->getName());
	// 2.
	if (password.empty())
		throw exceptionIRC(ERR_NEEDMOREPARAMS, ERRDESC_NEEDMOREPARAMS, "MODE");
	// 3.
	if (addMode && channel->getPassword().size() > 0)
		throw exceptionIRC(ERR_KEYSET, ERRDESC_KEYSET, channel->getName());
	// 4.
	if (!addMode && (password != channel->getPassword()))
		throw exceptionIRC(ERR_KEYSET, ERRDESC_KEYSET, channel->getName());
	else if (!addMode && (password == channel->getPassword()))
		channel->setPassword("");
	// 5.
	else if (addMode && channel->getPassword().empty())
		channel->setPassword(password);
}