#pragma once
#include "../user/User.hpp"
#include "../channel/Channel.hpp"
#include <map>

class User;
class Channel;

/*
	For each map (m_userChannels and m_channelUsers) the Connection is only allocated once.
	So for a new connection we do new Connection and then push back the pointer in
	m_userChannels's connection vector and m_channelUsers's connection vector
*/
struct	Connection {
	User		*user;
	Channel	*channel;
	bool	isInvited;
	bool	isOperator;
};

typedef std::map<const User *, std::vector<Connection *> >	UserConnections;
typedef std::map<Channel *, std::vector<Connection *> >	ChannelConnections;

class	MembershipRelation {
	private:
		UserConnections		m_userChannels;
		ChannelConnections	m_channelUsers;
		std::vector<Connection *>	m_empty;

	public:
		MembershipRelation();
		~MembershipRelation();

		const std::vector<Connection *>	&getUserChannels(const User *user) const;
		const UserConnections	&getUserChannels() const;
		const std::vector<Connection *>	&getChannelUsers(const Channel *channel) const;
		const ChannelConnections	&getChannelUsers() const;
		Channel	*getChannelByName(const std::string &channelName);

		std::vector<Connection *>	&getConnectionsByChannelName(const std::string &name);

		void	addNewChannel(Channel *channel, User *chOperator);	// Adds a new channel for the server
		void	addUserToChannel(User *member, Channel *channel, bool isInvite);	// Adds/Invites a user to a channel

		void	removeUserFromChannel(const User *user, Channel *channel);	// Removes a user from channel, frees the connection

		static bool	isUserInChannel(const User *user, const std::vector<Connection *> &channelUsers);
		static bool	isUserAMember(const User *user, const std::vector<Connection *> &channelUsers);
		static bool	isUserAnOperator(const User *user, const std::vector<Connection *> &channelUsers);

		static void	memberToOperator(const User *user, const std::vector<Connection *> &channelUsers);
		static void	operatorToMember(const User *user, const std::vector<Connection *> &channelUsers);

		static unsigned int	countOps(const std::vector<Connection *> &channelUsers);
};