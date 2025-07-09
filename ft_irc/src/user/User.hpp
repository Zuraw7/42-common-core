#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sstream>
#include <sys/socket.h>
#include <sys/types.h>
#include <map>
#include <netinet/in.h>
#include <netdb.h>
#include <cerrno>
#include <stdio.h>
#include "../../includes/ft_irc.hpp"
#include "../server/Server.hpp"
#include "../exceptionIRC/ExceptionIRC.hpp"
#include "utils.hpp"

class Server;

class User
{
	private:
		int m_userSocketFd;
		std::string m_ip;
		std::string m_message;
		std::string m_messageBuffer;
		sockaddr_in m_userAddr;
		socklen_t m_userSize;
		pollfd m_userPollfd;
		std::string m_nickname;
		std::string m_username;
		std::string m_realname;
		bool		m_correctServerPassword;
		bool		m_authenticationStatus;
		bool		m_negotiationStatus;
		std::string m_sendBuffer;
		size_t 		m_sendOffset;

	public:
		// Constructors and destructor
		User();
		User(const User &other);
		~User();

		// Getters
		int getUserSocketFd() const;
		std::string getIp() const;
		std::string getMessage() const;
		std::string getMessageBuffer() const;
		sockaddr_in getUserAddr() const;
		socklen_t getUserSize() const;
		std::string getNickname() const;
		std::string getUsername() const;
		std::string getRealname() const;
		bool		getCorrectServerPassword() const;
		bool		getAuthenticationStatus() const;
		bool		getNegotiationStatus() const;
		std::string	getSenderInfo() const;
		pollfd& getPollfd();

		// Setters
		void setUserSocketFd(const int fd);
		void setIp(const char *ip);
		void setIp(const std::string ip);
		void setMessage(const std::string &message);
		void setMessageBuffer(const std::string &messageBuffer);
		void setUserAddr(const sockaddr_in& addr);
		void setUserSize(const socklen_t addrSize);
		void setNickname(const std::string &nick, std::map<int, User *> &userList);
		void setUsername(const std::string &username);
		void setRealname(const std::string &realname);
		void setCorrectServerPassword(const bool correctPassword);
		void setAuthenticationStatus(const bool isAuthenticated);
		void setNegotiationStatus(const bool didNegotiate);

		// Methods
		void connectUserToServer(Server &server);
		void setInfo();
		static User	*getUserByNickname(std::map<int, User *> userList, const std::string& nickname);
		void initPollfd();
		void enqueueMessage(const std::string &message);
		void trySendMessage();
		void enablePollOut(bool status);

		// Operators

		const User	&operator=(const User &other);
		bool		operator==(const User &other);
};

#endif