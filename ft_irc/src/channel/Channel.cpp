#include "./Channel.hpp"

// Check if name meets IRC standard if not throw error 
void checkName(const std::string &name) {
	if (name.size() > 200)
		throw exceptionIRC(ERR_BADCHANMASK, ERRDESC_BADCHANMASK, name);

	if (name.empty() || (name[0] != '#' && name[0] != '&'))
		throw exceptionIRC(ERR_BADCHANMASK, ERRDESC_BADCHANMASK, name);

	for (size_t i = 1; i < name.size(); i++) {
		if (name[i] == ' ' || name[i] == '\a' || name[i] == ',')
			throw exceptionIRC(ERR_BADCHANMASK, ERRDESC_BADCHANMASK, name);
	}
}

Channel::Channel(std::string &name) : m_password(""), m_topic(""),  m_userLimit(-1), m_invOnlyStatus(false), m_topicSettableByOpOnly(true) {
	checkName(name);
	m_name = name;
}

Channel::Channel(std::string &name, std::string &password) : m_password(password), m_topic(""),  m_userLimit(-1), m_invOnlyStatus(false), m_topicSettableByOpOnly(true) {
	checkName(name);
	m_name = name;
}

Channel::Channel(const Channel &src) {
	*this = src;
}

Channel::~Channel() {}

Channel &Channel::operator=(const Channel &other) {
	if (this != &other) {
		m_name = other.m_name;
		m_password = other.m_password;
		m_invOnlyStatus = other.m_invOnlyStatus;
	}
	return *this;
}

// Getters
std::string Channel::getName() const {
	return m_name;
}

std::string Channel::getPassword() const {
	return m_password;
}

std::string Channel::getTopic() const {
	return m_topic;
}

bool Channel::getInvOnlyStatus() const {
	return m_invOnlyStatus;
}

int	Channel::getUserLimit() const {
	return m_userLimit;
}

bool	Channel::getTopicSettableByOpOnly() const {
	return m_topicSettableByOpOnly;
}


// Setters
void Channel::setPassword(const std::string &password) {
	m_password = password;
}

void Channel::setTopic(std::string &topic) {
	m_topic = topic;
}

void Channel::setInvOnlyStatus(bool status) {
	m_invOnlyStatus = status;
}

void	Channel::setUserLimit(int userLimit) {
	m_userLimit = userLimit;
}

void	Channel::setTopicSettableByOpOnly(bool status) {
	m_topicSettableByOpOnly = status;
}

// Methods

void sendRPL(int rplCode, User *recipient, const std::string &message) {
	std::stringstream ss;
	ss << rplCode;
	std::string rplCodeStr = ss.str();

	std::string reply = std::string(":") + SERVER_HOSTNAME + std::string(" ") + rplCodeStr + " " + recipient->getNickname() + " " + message + "\r\n";
	recipient->enqueueMessage(reply);
	logCommandToUser(reply, *recipient);
}

void Channel::sendUserList(User *recipient, const std::vector<Connection *> &channelUsers) const {
	std::string list = "= " + m_name + " :";
	for (std::vector<Connection *>::const_iterator it = channelUsers.begin(); it != channelUsers.end(); it++) {
		if ((*it)->isOperator) {
			list += "@";
		}
		list += (*it)->user->getNickname() + " ";
	}
	std::string endList = m_name + " :End of /NAMES list";

	sendRPL(RPL_NAMREPLY, recipient, list);
	sendRPL(RPL_ENDOFNAMES, recipient, endList);
}

void Channel::sendModeList(User *recipient) const {
	std::ostringstream	oss;
	oss << ":" << SERVER_HOSTNAME << " " << RPL_CHANNELMODEIS;
	oss << " " << recipient->getNickname() << " ";
	oss << m_name << " +";
	
	if (m_password != "")
		oss << 'k';
	if (m_topicSettableByOpOnly == true)
		oss << 't';
	if (m_invOnlyStatus == true)
		oss << 'i';
	if (m_userLimit > -1)
		oss << 'l';

	oss << " ";
	if (m_password != "")
		oss << m_password << " ";
	if (m_userLimit > -1)
		oss << m_userLimit << " ";
	oss << "\r\n";
	std::string	message = oss.str();
	recipient->enqueueMessage(message);
	logCommandToUser(message, *recipient);
}