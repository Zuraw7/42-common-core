#include <iostream>
#include "../includes/ScalarConverter.hpp"

int main (int argc, char **argv) {
	if (argc != 2) {
		std::cout << "Wrong usage! Correct use:" << std::endl;
		std::cout << "./convert <parameter>"<< std::endl;
		return 1;
	}
	ScalarConverter::convert(std::string(argv[1]));
	return 0;
}