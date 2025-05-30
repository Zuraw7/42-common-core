#include <iostream>
#include <sstream>
#include "../includes/ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {
	std::cout << "ScalarConverter default constructor called" << std::endl;
}

ScalarConverter::ScalarConverter(ScalarConverter const &src) {
	std::cout << "ScalarConverter copy constructor called" << std::endl;
	*this = src;
}

ScalarConverter::~ScalarConverter() {
	std::cout << "ScalarConverter destructor called" << std::endl;
}

ScalarConverter &ScalarConverter::operator=(ScalarConverter const &rhs) {
	std::cout << "ScalarConverter assignment operator called" << std::endl;
	if (this != &rhs) {
		// nothing to assing
	}
	return *this;
}

static void handleNan(void) {
	std::cout << "char: impossible" << std::endl;
	std::cout << "int: impossible" << std::endl;
	std::cout << "float: nanf" << std::endl;
	std::cout << "double: nan" << std::endl;
}

static void handleInf(const std::string &number) {
	std::cout << "char: impossible" << std::endl;
	std::cout << "int: impossible" << std::endl;
	std::cout << "float: " << number << "f" << std::endl;
	std::cout << "double: " << number << std::endl;
}

static bool stringToInt(const std::string &number, int &value) {
	std::istringstream iss(number);
	iss >> value;
	return !iss.fail() && iss.eof();
}

static bool stringToFloat(const std::string &number, float &value) {
	std::string floatStr = number;
	if (floatStr[floatStr.length() - 1] == 'f') {
		floatStr = floatStr.substr(0, floatStr.length() - 1);
	}
	std::istringstream iss(floatStr);
	iss >> value;
	return !iss.fail() && iss.eof();
}

static bool stringToDouble(const std::string &number, double &value) {
	std::istringstream iss(number);
	iss >> value;
	return !iss.fail() && iss.eof();
}

static bool stringToChar(const std::string &number, char &value) {
	if (number.length() == 3 && number[0] == '\'' && number[2] == '\'') {
		value = number[1];
		return true;
	} else if (number.length() == 1) {
		value = number[0];
		return true;
	}
	return false;
}

void ScalarConverter::convert(const std::string &number) {
	if (!number.compare("nan") || !number.compare("nanf")) {
		handleNan();
		return;
	}
	
	if (!number.compare("-inf") || !number.compare("+inf") || !number.compare("-inff") || !number.compare("+inff")) {
		handleInf(number);
		return;
	}

	char	charValue;
	int		intValue;
	float	floatValue;
	double	doubleValue;

	if (stringToInt(number, intValue)) {
		std::cout << "int" << std::endl;
		floatValue = static_cast<float>(intValue);
		doubleValue = static_cast<double>(intValue);
		charValue = static_cast<char>(intValue);
	} else if (stringToDouble(number, doubleValue)) {
		std::cout << "double" << std::endl;
		floatValue = static_cast<float>(doubleValue);
		intValue = static_cast<int>(doubleValue);
		charValue = static_cast<char>(doubleValue);
	} else if (stringToFloat(number, floatValue)) {
		std::cout << "float" << std::endl;
		intValue = static_cast<int>(floatValue);
		doubleValue = static_cast<double>(floatValue);
		charValue = static_cast<char>(floatValue);
	} else if (stringToChar(number, charValue)) {
		std::cout << "char" << std::endl;
		intValue = static_cast<int>(charValue);
		floatValue = static_cast<float>(charValue);
		doubleValue = static_cast<double>(charValue);
	} else {
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
		return;
	}

	if (isprint(charValue)) {
		std::cout << "char: '" << charValue << "'" << std::endl;
	} else {
		std::cout << "char: Non displayable" << std::endl;
	}

	std::cout << "int: " << intValue << std::endl;
	std::cout << "float: " << floatValue << "f" << std::endl;
	std::cout << "double: " << doubleValue << std::endl;
}