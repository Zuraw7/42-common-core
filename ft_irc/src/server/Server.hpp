#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <exception>
#include <poll.h>
#include <vector>
#include <map>
#include <fcntl.h>
#include "../membership/Membership.hpp"
#include "../user/User.hpp"
#include "../channel/Channel.hpp"

class User;
class Channel;
class MembershipRelation;
typedef std::vector<std::string>	command;

#define SERVER_HOSTNAME "localhost"

class Server
{
	private:
		int m_port;
		int m_servSocketFd;
		int	m_option;
		std::string m_password;	
		sockaddr_in m_serverAddr;	// server informations
		pollfd m_serverPollFd;
		std::map<int, User *> m_users;	// stores users based on their fd
		std::vector<pollfd> m_fds;	// stores server and all users fds
		MembershipRelation		*m_membership; //contains the connections and channels

		Server();
		Server(const Server &other);
		const Server &operator=(const Server &other);

	public:
		// Constructors and destructor
		Server(int port, std::string &password);
		~Server();

		// Getters
		int getPort() const;
		int getSocketFd() const;
		const sockaddr_in getServerAddr() const;
		int	getOption() const;
		const std::string& getPassword() const;
		pollfd& getServerPollfd();
		std::map<int, User *>& getUsers();
		std::vector<pollfd>& getFds();
		MembershipRelation &getMembership();

		// Setters
		void setPort(int port);
		void setServSocketFd(int fd);
		void setOption(int opt);
		void setPassword(std::string &password);

		// Methods
		void createSocket(void);
		void bindSocket(void);
		void initPollfd(void);
		void acceptUserConnection(void);
		void disconnectUser(int fd, command &argv);
		void shutdown();
};

#endif