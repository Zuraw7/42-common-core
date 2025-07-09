#include "./Server.hpp"

Server::Server(int port, std::string& password) : m_port(port), m_servSocketFd(-1), m_option(0), m_password(password) {
	m_membership = new MembershipRelation;
}

Server::Server(const Server &other)
{
	m_servSocketFd = other.m_servSocketFd;
	m_port = other.m_port;
}

Server::~Server()
{
	if (m_servSocketFd != -1 && close(m_servSocketFd) == -1) {
		std::cerr << "Error closing socket" << std::endl;
	}
	delete m_membership;
	std::cout << "Server socket has been closed" << std::endl;
}

// Getters
int Server::getPort() const
{
	return (m_port);
}

const sockaddr_in Server::getServerAddr() const {
	return (m_serverAddr);
}

int Server::getSocketFd() const
{
	return (m_servSocketFd);
}

int Server::getOption() const {
	return m_option;
}

const std::string& Server::getPassword() const {
	return m_password;
}

pollfd& Server::getServerPollfd() {
	return m_serverPollFd;
}

std::map<int, User *>& Server::getUsers() {
	return m_users;
}

std::vector<pollfd>& Server::getFds() {
	return m_fds;
}

MembershipRelation &Server::getMembership() {
	return *m_membership;
}

// Setters
void Server::setPort(int port) {
	m_port = port;
}

void Server::setServSocketFd(int fd) {
	m_servSocketFd = fd;
}

void Server::setOption(int opt) {
	m_option = opt;
}

void Server::setPassword(std::string &password) {
	m_password = password;
}

// Methods
// Creates a server socket, throws an exception on error
void Server::createSocket(void) {
	m_servSocketFd = socket(AF_INET, SOCK_STREAM, 0);
	if (m_servSocketFd == -1) {
		throw std::runtime_error("Failed to create server socket");
	}
	setOption(1);
	setsockopt(m_servSocketFd, SOL_SOCKET, SO_REUSEADDR, &m_option, sizeof(m_option)); // Allows to reuse port

	// Set server socket to non-blocking mode
	if (fcntl(m_servSocketFd, F_SETFL, O_NONBLOCK) == -1) {
		throw std::runtime_error("Failed to set socket to non-blocking mode");
	}

	std::cout << "Server socket " << m_servSocketFd << " has been created" << std::endl; 
}

/*
	1. Binds the server socket to IP address 0.0.0.0 (all available interfaces) and port 6667
	2. Sets the server socket to listen for incoming connections. Throws exceptions on errors
*/
void Server::bindSocket(void) {
	// 1.
	m_serverAddr.sin_family = AF_INET;
	m_serverAddr.sin_port = htons(m_port);
	inet_pton(AF_INET, "0.0.0.0", &m_serverAddr.sin_addr);
	if (bind(m_servSocketFd, (sockaddr *)&m_serverAddr, sizeof(m_serverAddr)) == -1) {
		throw std::runtime_error("Failed to bind to IP/port");
	}
	std::cout << "Server is bind to port " << m_port << std::endl;
	// 2.
	if (listen(m_servSocketFd, SOMAXCONN) == -1) {
		throw std::runtime_error("Failed to listen");
	}
	std::cout << "Server listens for clients " << std::endl;
}

void Server::initPollfd(void) {
	m_serverPollFd.fd = m_servSocketFd;
	m_serverPollFd.events = POLLIN;
	m_serverPollFd.revents = 0;
}

void Server::acceptUserConnection(void) {
	User *user = new User;
	if (m_password.empty()) {
		user->setCorrectServerPassword(true);
	}
	try {
		user->connectUserToServer(*this);
		user->setInfo();
	} catch (const std::runtime_error &e) {
		std::cout << "Error: " << e.what() << std::endl;
	}
	user->initPollfd();
	m_fds.push_back(user->getPollfd());
	m_users[user->getUserSocketFd()] = user;
}

/*
	1. Get user's quit reason and build QUIT message
	2. Get all user channels
	3. Send QUIT message to all users in the channels
	4. Remove user from all channels
	5. Notice in the server that user has disconnected and delete the user
*/
void Server::disconnectUser(int fd, command &argv) {

	std::map<int, User *>::iterator it = m_users.find(fd);
	if (it == m_users.end()) {
		return;
	}
	User *user = it->second;

	// 1.
	std::string	reason;
	if (argv.size() == 1)
		reason = "";
	else if (argv.size() >= 2)
		reason = argv.at(1);
	std::string	response = buildCommand(user->getSenderInfo(), "QUIT", reason);

	// 2.
	std::vector<Connection *> userChannels = m_membership->getUserChannels(user);
	if (!userChannels.empty()) {
		// 3.
		std::set<User *> notifiedUsers;
		// in each channel
		for (std::vector<Connection *>::iterator it = userChannels.begin(); it != userChannels.end(); it++) {
			std::vector<Connection *> channelUsers = m_membership->getChannelUsers((*it)->channel);
			// for each user
			for (std::vector<Connection *>::iterator uIt = channelUsers.begin(); uIt != channelUsers.end(); uIt++) {
				// if user in channel is not the current user
				if ((*uIt)->user->getNickname() != user->getNickname()) {
					// check if he has been already notified if not send the message
					if (notifiedUsers.insert((*uIt)->user).second) {
						(*uIt)->user->enqueueMessage(response);
						logCommandToUser(response, *(*uIt)->user);
					}
				}
			}
			// 4.
			m_membership->removeUserFromChannel(user, (*it)->channel);
		}
	}
	// 5.
	delete it->second;
	m_users.erase(it);

	for (std::vector<pollfd>::iterator fIt = m_fds.begin(); fIt != m_fds.end(); fIt++) {
		if (fIt->fd == fd) {
			fIt->fd = -1;
			m_fds.erase(fIt);
			break;
		}
	}
}

// Operators
const Server &Server::operator=(const Server &other)
{
	if (this != &other) {
		m_port = other.m_port;
		m_servSocketFd = other.m_servSocketFd;
	}
	return (*this);
}

// Shuts down the server
// Clears the users map and fds vector
void Server::shutdown() {
	std::cout << "Shutting down server..." << std::endl;

	for (std::map<int, User*>::iterator it = m_users.begin(); it != m_users.end(); ++it) {
		if (it->second) {
			// remove user from all channels
			std::vector<Connection *> userChannels = m_membership->getUserChannels(it->second);
			for (std::vector<Connection *>::iterator chIt = userChannels.begin(); chIt != userChannels.end(); ++chIt) {
				m_membership->removeUserFromChannel(it->second, (*chIt)->channel);
			}
			// send QUIT message to the user
			std::string quitMessage = buildCommand(it->second->getSenderInfo(), "QUIT", ":Server is shutting down");
			it->second->enqueueMessage(quitMessage);
			logCommandToUser(quitMessage, *it->second);
			// delete user
			delete it->second;
		}
	}
	m_users.clear();

	m_fds.clear();
}
