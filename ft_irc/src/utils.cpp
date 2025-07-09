#include "utils.hpp"
#include <string>
#include <vector>
#include <sstream>

bool	isIn(char needle, const char *haystack) {
	for (int i = 0; haystack[i]; i++) {
		if (needle == haystack[i])
			return true;
	}
	return false;
}

std::size_t	ft_strlen(const char string[]) {
	std::size_t	result = 0;

	if (string == NULL)
		return 0;
	while (string[result])
		result++;
	return result;
}

int	ft_atoi(const std::string &num) {
	int	result;
	int	change_sign;
	std::string::const_iterator	str = num.begin();

	result = 0;
	while ((*str >= 7 && *str <= 13) || *str == 32)
		str++;
	change_sign = (*str == '-') * -2 + 1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str && *str >= '0' && *str <= '9')
	{
		result *= 10;
		result += (*str - '0');
		str++;
	}
	return (change_sign * result);
}

std::vector<std::string> split(const std::string &str, char delimiter) {
	std::vector<std::string> tokens;
	std::stringstream ss(str);
	std::string token;
	while (std::getline(ss, token, delimiter)) {
		tokens.push_back(token);
	}
	return tokens;
}

bool	isDigits(std::string string, char begin_after, char end_before)
{
	std::string::iterator	it = string.begin();
	std::size_t				begin_pos = string.find(begin_after);

	if (begin_pos != string.npos && begin_after != '\0')
		it += begin_pos + 1;
	while (it < string.end() && *it != end_before)
	{
		if (*it > '9' || *it < '0')
			return false;
		it++;
	}
	return true;
}

bool isValidNumber(const std::string &str) {
	for (size_t i = 0; i < str.length(); i++) {
		if (!std::isdigit(str[i])) {
			return false;
		}
	}
	return true;
}

int checkArgv(int argc, char **argv, int &port) {
	if (argc != 3) {
		std::cout << "Usage: ./ircserv <port> <password>" << std::endl;
		return 1;
	}

	std::string strPort = argv[1];
	if (!isValidNumber(strPort)) {
		std::cerr << "Error: Port must be a number" << std::endl;
		return 1;
	}

	std::istringstream iss(strPort);
	iss >> port;

	if (port < 1024 || port > 65535) {
		std::cerr << "Error: Port must be between 1024 and 65535" << std::endl;
		return 1;
	}
	return 0;
}
