#include "User.hpp"

std::string	buildWelcomeMessage(const std::string &recipientNickname);

// Constructors and deconstructors
User::User() : m_userSocketFd(-1), m_ip(""), m_message(""), m_messageBuffer(""), m_nickname(""), m_username(""), m_realname(""), m_correctServerPassword(false), m_authenticationStatus(false), m_negotiationStatus(false), m_sendBuffer(""), m_sendOffset(0)
{
	m_userSize = sizeof(m_userAddr);
}

User::User(const User &other)
{
	m_userSocketFd = other.m_userSocketFd;
	m_correctServerPassword = other.m_correctServerPassword;
	m_ip = other.m_ip;
	m_message = other.m_message;
	m_messageBuffer = other.m_messageBuffer;
	m_userAddr = other.m_userAddr;
	m_userSize = other.m_userSize;
}

// Add removing from all channels on exit
User::~User()
{
	if (m_userSocketFd != -1 && close(m_userSocketFd) == -1) {
		std::cerr << "Error closing user socket" << std::endl;
	}
	std::cout << m_nickname << " socket has been closed" << std::endl;
}

// Getters
int User::getUserSocketFd() const {
	return m_userSocketFd;
}

std::string User::getIp() const {
	return m_ip;
}

std::string User::getMessage() const {
	return m_message;
}

std::string User::getMessageBuffer() const {
	return m_messageBuffer;
}

sockaddr_in User::getUserAddr() const {
	return m_userAddr;
}

socklen_t User::getUserSize() const {
	return m_userSize;
}

std::string User::getNickname() const {
	return m_nickname;
}

std::string User::getUsername() const {
	return m_username;
}

std::string User::getRealname() const {
	return m_realname;
}

bool User::getCorrectServerPassword() const {
	return m_correctServerPassword;
}

bool		User::getAuthenticationStatus() const {
	return m_authenticationStatus;
}

bool		User::getNegotiationStatus() const {
	return m_negotiationStatus;
}

std::string	User::getSenderInfo() const {
	return std::string(":").append(m_nickname);
}

pollfd& User::getPollfd() {
	return m_userPollfd;
}

// Setters
void User::setUserSocketFd(const int fd) {
	m_userSocketFd = fd;
}

void User::setIp(const char *ip) {
	m_ip = ip;
}

void User::setIp(const std::string ip) {
	m_ip = ip;
}

void User::setMessage(const std::string &message) {
	if (message.length() > MAX_COMMAND_LENGTH) {
		std::cout << "Error: Message too long" << std::endl;
		m_message = "";
	} else {
		m_message = message;
	}
}

void User::setMessageBuffer(const std::string &messageBuffer) {
	if (messageBuffer.length() > MAX_COMMAND_LENGTH) {
		std::cout << "Error: Message buffer too long" << std::endl;
		m_messageBuffer = "";
	} else {
		m_messageBuffer = messageBuffer;
	}
}

void User::setUserAddr(const sockaddr_in &addr) {
	m_userAddr = addr;
}

void User::setUserSize(const socklen_t addrSize) {
	m_userSize = addrSize;
}

void User::setNickname(const std::string &nick, std::map<int, User *> &userList) {
	char	allowed[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789[]-{}\\^'";
	char	firstLetterAllowed[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	
	if (nick.empty())
		throw exceptionIRC(ERR_NONICKNAMEGIVEN, ERRDESC_NONICKNAMEGIVEN);
	for (std::string::const_iterator it = nick.begin(); it != nick.end(); it++) {
		if (it == nick.begin() && !isIn(*it, firstLetterAllowed))
			throw exceptionIRC(ERR_ERRONEUSNICKNAME, ERRDESC_ERRONEUSNICKNAME, nick);
		else if (!isIn(*it, allowed))
			throw exceptionIRC(ERR_ERRONEUSNICKNAME, ERRDESC_ERRONEUSNICKNAME, nick);
	}
	if (nick == m_nickname)
		return ;
	for (std::map<int, User *>::iterator it = userList.begin(); it != userList.end(); it++) {
		if (nick == it->second->getNickname())
			throw exceptionIRC(ERR_NICKNAMEINUSE, ERRDESC_NICKNAMEINUSE, nick);
	}
	m_nickname = nick;
}

void User::setUsername(const std::string &username) {
	m_username = username;
}

void User::setRealname(const std::string &realname) {
	if (realname == "")
		return ;
	else if (realname.at(0) == ':')
		m_realname = realname.substr(1);
	else
		m_realname = realname;
}

void User::setCorrectServerPassword(const bool correctPassword) {
	m_correctServerPassword = correctPassword;
}

void User::setAuthenticationStatus(const bool isAuthenticated) {
	if (!m_correctServerPassword)
		return;
	if (!m_authenticationStatus && isAuthenticated) {
		std::string message = buildWelcomeMessage(m_nickname);
		enqueueMessage(message);
		logCommandToUser(message, *this);
		message = buildMessageOfTheDay(m_nickname);
		enqueueMessage(message);
		logCommandToUser(message, *this);
	}
	m_authenticationStatus = isAuthenticated;
}

void User::setNegotiationStatus(const bool didNegotiate) {
	m_negotiationStatus = didNegotiate;
}

// Methods
void User::connectUserToServer(Server &server) {
	m_userSocketFd = accept(server.getSocketFd(), (sockaddr *)&m_userAddr, &m_userSize);

	if (m_userSocketFd == -1) {
		throw std::runtime_error("User couldn't connect to the server");
	}
	// Set user socket to non-blocking mode
	if (fcntl(m_userSocketFd, F_SETFL, O_NONBLOCK) == -1) {
		throw std::runtime_error("Failed to set socket to non-blocking mode");
	}
}

/*
	1. Get and set user's IP addres
	2. Prepare struct to get user's info
	3. Get and set user's name
*/
void User::setInfo() {
	// 1.
	char ipStr[INET_ADDRSTRLEN];
	if (inet_ntop(AF_INET, &m_userAddr.sin_addr, ipStr, sizeof(ipStr)) == NULL) {
		throw std::runtime_error("Error converting IP address");
	}
	m_ip = std::string(ipStr);
	
	// 2.
	struct addrinfo hints, *res;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	
	int status = getaddrinfo(m_ip.c_str(), NULL, &hints, &res);
	if (status != 0) {
		std::string errorMsg = gai_strerror(status);
		throw std::runtime_error("Error in getaddrinfo: " + errorMsg);
	}
	
	// 3.
	char host[NI_MAXHOST];
	status = getnameinfo(res->ai_addr, res->ai_addrlen, host, sizeof(host), NULL, 0, NI_NAMEREQD);
	if (status != 0) {
		std::cerr << "Error in getnameinfo: " << gai_strerror(status) << std::endl;
		std::cout << "Unknown host (" << ") connected on port " << ntohs(m_userAddr.sin_port) << std::endl;
	} else {
		std::cout << "User: " << m_nickname << " (" << m_ip << ") connected on port " << ntohs(m_userAddr.sin_port) << std::endl;
	}

	freeaddrinfo(res);
}

void User::initPollfd() {
	m_userPollfd.fd = m_userSocketFd;
	m_userPollfd.events = POLLIN;
	m_userPollfd.revents = 0;
}

User	*User::getUserByNickname(std::map<int, User *> userList, const std::string& nickname) {
	if (nickname == "" || userList.empty())
		return NULL;
	for (std::map<int, User *>::iterator it = userList.begin(); it != userList.end(); it++) {
		if (it->second->getNickname() == nickname)
			return it->second;
	}
	return NULL;
}

/*
	1. If sendOffset is equal to the size of the sendBuffer, clear the buffer and reset the offset (this means that the buffer is empty or all data has been sent).
	2. Append the message to the sendBuffer.
	3. Call trySendMessage to attempt sending the message.
*/
void User::enqueueMessage(const std::string &message) {
	// 1.
	if (m_sendOffset == m_sendBuffer.size()) {
		m_sendBuffer.clear();
		m_sendOffset = 0;
	}
	// 2.
	m_sendBuffer.append(message);
	// 3.
	trySendMessage();
}

/*
	1. While there are bytes to send
	2. Try to send the data from the sendBuffer starting from the current offset.
	3. If send fails with EAGAIN or EWOULDBLOCK, enable POLLOUT event and return (this means that the socket is not ready to send data).
	4. If send is successful, update the sendOffset by the number of bytes sent.
	5. If all data has been sent, disable POLLOUT event, clear the sendBuffer, and reset the sendOffset.
*/
void User::trySendMessage() {
	// 1.
	while (m_sendOffset < m_sendBuffer.size()) {
		// 2.
		ssize_t bytesSent = send(m_userSocketFd, m_sendBuffer.c_str() + m_sendOffset, m_sendBuffer.size() - m_sendOffset, MSG_NOSIGNAL);
		// 3.
		if (bytesSent == -1) {
			if (errno == EAGAIN || errno == EWOULDBLOCK) {
				enablePollOut(true);
				return;
			} else if (errno == EPIPE) {
				return;
			}
		}
		// 4.
		m_sendOffset += bytesSent;
	}
	// 5.
	enablePollOut(false);
	m_sendBuffer.clear();
	m_sendOffset = 0;
}

// Enable or disable POLLOUT event
void User::enablePollOut(bool status) {
	if (status) {
		m_userPollfd.events |= POLLOUT;
	} else {
		m_userPollfd.events &= ~POLLOUT;
	}
}

// Operators
const User &User::operator=(const User &other)
{
	if (this != &other){
		m_userSocketFd = other.m_userSocketFd;
	}
	return (*this);
}

bool		User::operator==(const User &other) {
	if (m_userSocketFd == other.m_userSocketFd && m_nickname == other.m_nickname)
		return true;
	return false;
}
