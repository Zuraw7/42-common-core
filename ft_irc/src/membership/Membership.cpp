#include "Membership.hpp"

MembershipRelation::MembershipRelation() {}

MembershipRelation::~MembershipRelation() {
	for (ChannelConnections::iterator it = m_channelUsers.begin(); it != m_channelUsers.end(); it++) {
		while (!it->second.empty()) {
			delete it->second.back();
			it->second.pop_back();
		}
		delete it->first;
	}
}

Channel	*MembershipRelation::getChannelByName(const std::string &channelName) {
	for (ChannelConnections::iterator it = m_channelUsers.begin(); it != m_channelUsers.end(); it++) {
		if (it->first->getName() == channelName)
			return it->first;
	}
	return NULL;
}

const std::vector<Connection *>	&MembershipRelation::getUserChannels(const User *user) const {
	static const std::vector<Connection *> empty;
	UserConnections::const_iterator it = m_userChannels.find(const_cast<User *>(user));
	if (it != m_userChannels.end()) {
		return it->second;
	}
	return empty;
}

const UserConnections	&MembershipRelation::getUserChannels() const {
	return m_userChannels;
}

const std::vector<Connection *>	&MembershipRelation::getChannelUsers(const Channel *channel) const {
	static const std::vector<Connection *> empty;
	ChannelConnections::const_iterator it = m_channelUsers.find(const_cast<Channel *>(channel));
	if (it != m_channelUsers.end()) {
		return it->second;
	}
	return empty;
}

const ChannelConnections	&MembershipRelation::getChannelUsers() const {
	return m_channelUsers;
}

// returns the connections between one channel and multiple users
std::vector<Connection *>	&MembershipRelation::getConnectionsByChannelName(const std::string &name) {
	for (ChannelConnections::iterator it = m_channelUsers.begin(); it != m_channelUsers.end(); it++) {
		if (it->first->getName() == name) {
			return it->second;
		}
	}
	return m_empty;
}

void	MembershipRelation::addNewChannel(Channel *channel, User *chOperator) {
	Connection *newConnection = new Connection;
	newConnection->channel = channel;
	newConnection->user = chOperator;
	newConnection->isInvited = false;
	newConnection->isOperator = true;
	std::vector<Connection*> channelList;
	channelList.push_back(newConnection);
	m_channelUsers.insert(std::make_pair(channel, channelList));
	try
	{
		std::vector<Connection*>	&userChannels = m_userChannels.at(chOperator);
		userChannels.push_back(newConnection);
	}
	catch (const std::out_of_range &e)
	{
		std::vector<Connection*> userList;
		userList.push_back(newConnection);
		m_userChannels.insert(std::make_pair(chOperator, userList));
	}
}

/*
	Adds the user to a specific channel, can throw ERR_USERONCHANNEL. The channel has to be created previously using MembershipRelation::addNewChannel
	
	1. user is not on any channels, we add the pair to m_userChannels
	2. user is on some channels, we push back the connection
	3. user is on that channel as invited, but now he joins
	4. inviting user that is already invited, leave the connection as is
	5. user is on that channel as a member or an op, we throw
*/
void	MembershipRelation::addUserToChannel(User *member, Channel *channel, bool isInvite) {
	try
	{
		std::vector<Connection *>	&channelList = m_userChannels.at(member);
		// 2, 3, 4, 5
		for (std::vector<Connection *>::iterator it = channelList.begin(); it != channelList.end(); it++) {
			if ((*it)->channel == channel && (*it)->isInvited == true && isInvite == false) {
				(*it)->isInvited = false; // 3
				return;
			} else if ((*it)->channel == channel && (*it)->isInvited == true && isInvite == true) {
				return ; // 4
			} else if ((*it)->channel == channel) {
				throw exceptionIRC(ERR_USERONCHANNEL, ERRDESC_USERONCHANNEL, (member->getNickname() + " " + channel->getName())); // 4
			}
		}
		// 2
		if (channel->getUserLimit() > -1 && channel->getUserLimit() <= static_cast<int>(MembershipRelation::getChannelUsers(channel).size()))
			throw exceptionIRC(ERR_CHANNELISFULL, ERRDESC_CHANNELISFULL, channel->getName());
		if (channel->getInvOnlyStatus() == true && isInvite == false)
			throw exceptionIRC(ERR_INVITEONLYCHAN, ERRDESC_INVITEONLYCHAN, channel->getName());
		Connection *newConnection = new Connection;
		newConnection->user = member;
		newConnection->channel = channel;
		newConnection->isInvited = isInvite;
		newConnection->isOperator = false;
		channelList.push_back(newConnection);
		m_channelUsers.at(channel).push_back(newConnection);
	}
	catch (const std::out_of_range &e)
	{
		// 1
		if (channel->getUserLimit() > -1 && channel->getUserLimit() <= static_cast<int>(MembershipRelation::getChannelUsers(channel).size()))
			throw exceptionIRC(ERR_CHANNELISFULL, ERRDESC_CHANNELISFULL, channel->getName());
		if (channel->getInvOnlyStatus() == true && isInvite == false)
			throw exceptionIRC(ERR_INVITEONLYCHAN, ERRDESC_INVITEONLYCHAN, channel->getName());
		Connection *newConnection = new Connection;
		newConnection->user = member;
		newConnection->channel = channel;
		newConnection->isInvited = isInvite;
		newConnection->isOperator = false;
		std::vector<Connection *>	channelList;
		channelList.push_back(newConnection);
		m_userChannels.insert(std::make_pair(member, channelList));
		m_channelUsers.at(channel).push_back(newConnection);
	}
}

void	MembershipRelation::removeUserFromChannel(const User *user, Channel *channel) {
	std::vector<Connection *>	&channelUsers = m_channelUsers.at(channel);
	std::vector<Connection *>	&userChannels = m_userChannels.at(user);
	bool	found = false;

	for (std::vector<Connection *>::iterator it = channelUsers.begin(); it != channelUsers.end(); it++) {
		if ((*it)->user == user) {
			channelUsers.erase(it);
			found = true;
			break;
		}
	}
	for (std::vector<Connection *>::iterator it = userChannels.begin(); it != userChannels.end(); it++) {
		if ((*it)->channel == channel) {
			Connection	*toFree = (*it);
			userChannels.erase(it);
			delete toFree;
			found = true;
			break;
		}
	}
	if (!found)
		throw exceptionIRC(ERR_USERNOTINCHANNEL, ERRDESC_USERNOTINCHANNEL, user->getNickname() + " " + channel->getName());
	if (m_channelUsers.at(channel).size() == 0) {
		m_channelUsers.erase(channel);
		delete channel;
	}
}

// Check if user is in the channel
bool	MembershipRelation::isUserInChannel(const User *user, const std::vector<Connection *> &channelUsers) {
	for (std::vector<Connection *>::const_iterator it = channelUsers.begin(); it != channelUsers.end(); it++) {
		if ((*it)->user == user && (*it)->isInvited == false)
			return true;
	}
	return false;
}

// Check if user is a member of the channel (member/operator)
bool	MembershipRelation::isUserAMember(const User *user, const std::vector<Connection *> &channelUsers) {
	for (std::vector<Connection *>::const_iterator it = channelUsers.begin(); it != channelUsers.end(); it++) {
		if ((*it)->user == user && (*it)->isInvited == false && (*it)->isOperator == false)
			return true;
	}
	return false;
}

// Check if user is an operator of the channel
bool	MembershipRelation::isUserAnOperator(const User *user, const std::vector<Connection *> &channelUsers) {
	for (std::vector<Connection *>::const_iterator it = channelUsers.begin(); it != channelUsers.end(); it++) {
		if ((*it)->user == user && (*it)->isInvited == false && (*it)->isOperator == true)
			return true;
	}
	return false;
}

void	MembershipRelation::memberToOperator(const User *user, const std::vector<Connection *> &channelUsers) {
	for (std::vector<Connection *>::const_iterator it = channelUsers.begin(); it != channelUsers.end(); it++) {
		if ((*it)->user == user && (*it)->isInvited == false && (*it)->isOperator == false)
			(*it)->isOperator = true;
	}
}

void	MembershipRelation::operatorToMember(const User *user, const std::vector<Connection *> &channelUsers) {
	for (std::vector<Connection *>::const_iterator it = channelUsers.begin(); it != channelUsers.end(); it++) {
		if ((*it)->user == user && (*it)->isInvited == false && (*it)->isOperator == true)
			(*it)->isOperator = false;
	}
}

unsigned int	MembershipRelation::countOps(const std::vector<Connection *> &channelUsers) {
	unsigned int	result = 0;

	for (std::vector<Connection *>::const_iterator it = channelUsers.begin(); it != channelUsers.end(); it++) {
		if ((*it)->isInvited == false && (*it)->isOperator == true)
			result++;
	}
	return result;
}