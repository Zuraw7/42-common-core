#include "ExceptionIRC.hpp"

// Constructors

exceptionIRC::exceptionIRC(int errorCode, const char errorDescription[]) : std::invalid_argument(errorDescription), m_errorCode(errorCode), m_errorDescription(errorDescription), m_parameter() {}
exceptionIRC::exceptionIRC(int errorCode, const char errorDescription[], std::string parameter) : std::invalid_argument(errorDescription), m_errorCode(errorCode), m_errorDescription(errorDescription), m_parameter(parameter) {}

// Destructors

exceptionIRC::~exceptionIRC() throw() {}

// Getters

unsigned int		exceptionIRC::getErrorCode() const {
	return m_errorCode;
}

const std::string	&exceptionIRC::getErrorDescription() const {
	return m_errorDescription;
}

const std::string	&exceptionIRC::getParameter() const {
	return m_parameter;
}

// Methods

// Returns a string containing the properly formatted error message.
std::string	exceptionIRC::buildErrorMessage(const std::string &userNickname) const {
	std::ostringstream oss;
	oss << ":" << SERVER_HOSTNAME << " " << m_errorCode << " ";
	oss << (userNickname.empty() ? "* " : userNickname + " ");

	std::size_t	pos = m_errorDescription.find("%s");
	if (pos != m_errorDescription.npos) {
		oss << m_errorDescription.substr(0, pos);
		oss << m_parameter;
		if (pos + 2 < m_errorDescription.length())
			oss << m_errorDescription.substr(pos + 2);
	} else
		oss << m_errorDescription;
	oss << "\r\n";

	return oss.str();
}