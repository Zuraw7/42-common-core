#pragma once

#include <stdexcept>
#include <sstream>
#include "../server/Server.hpp" // for server hostname
#include "errorsList.hpp"

/*
	exceptionIRC(int errorCode, char errorDescription[]);
	
	or for parametized errors
	exceptionIRC(int errorCode, char errorDescription[], std::string parameter);
*/
class exceptionIRC : public std::invalid_argument {
	public:
		// Constructors

		exceptionIRC(int errorCode, const char errorDescription[]);
		exceptionIRC(int errorCode, const char errorDescription[], std::string parameter);
		
		// Destructors

		~exceptionIRC() throw();

		// Getters

		unsigned int		getErrorCode() const;
		const std::string	&getErrorDescription() const;
		const std::string	&getParameter() const;

		// Methods

		std::string	buildErrorMessage(const std::string &userNickname) const;
	
	private:
		const unsigned int			m_errorCode;
		const std::string			m_errorDescription;
		const std::string			m_parameter;
};

