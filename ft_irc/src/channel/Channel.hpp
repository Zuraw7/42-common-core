#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include <map>

#include "../user/User.hpp"
#include "../exceptionIRC/ExceptionIRC.hpp"
#include "../exceptionIRC/replyList.hpp"
#include "../membership/Membership.hpp"

typedef std::vector<std::string>	command;
typedef std::vector<command>	commands;

class User;
class exceptionIRC;
class MembershipRelation;
struct Connection;

/*
	Channel is created implicitly when the first client joins it
	Channel exists as long as there is at least 1 user
	Users can join the channel by channels name

	Channels names are string (starting with '&' or '#') of length up to 200 characters
		channel name cannot contain any space ' ', control G ('^G' or ASCII 7), and comma ','
		channels with '#' prefix are available across an entire IRC network, those with '&' prefix are local only

	To join channel user types JOIN channel
		- if channel exist user joins channel
		- if channel doesnt exist, channel is created and user becomes chop

	User may not be able to join based on channel's mode -> (+i) invite-only
*/
class Channel {
	private:
		std::string				m_name;
		std::string				m_password;
		std::string				m_topic;
		int						m_userLimit;
		bool					m_invOnlyStatus;
		bool					m_topicSettableByOpOnly;

		Channel();

	public:
		// Constructors and destructor
		Channel(std::string &name);
		Channel(std::string &name, std::string &password);
		Channel(const Channel &src);
		~Channel();

		Channel &operator=(const Channel &other);

		// Getters
		std::string getName() const;
		std::string getPassword() const;
		std::string getTopic() const;
		int	getUserLimit() const;
		
		bool	getInvOnlyStatus() const;
		bool	getTopicSettableByOpOnly() const;

		// Setters
		void 	setPassword(const std::string &password);
		void 	setInvOnlyStatus(bool status);
		void 	setTopic(std::string &topic);
		void	setUserLimit(int userLimit);
		void	setTopicSettableByOpOnly(bool status);

		// Methods
		void sendUserList(User *recipient, const std::vector<Connection *> &channelUsers) const;
		void sendModeList(User *recipient) const;
};

void checkName(const std::string &name);
void sendRPL(int rplCode, User *recipient, const std::string &message);
void handleKick(command &argv, std::map<int, User *> &users, int socketFd, MembershipRelation &membership);
void handleTopic(command &argv, std::map<int, User *> &users, int socketFd, MembershipRelation &membership);
void handleInvite(command &argv, std::map<int, User *> &users, int socketFd, MembershipRelation &membership);
void handleMode(command &argv, std::map<int, User *> &users, int socketFd, MembershipRelation &membership);

#endif