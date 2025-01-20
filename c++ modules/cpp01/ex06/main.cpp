#include <iostream>
#include "Harl.hpp"

int main(int argc, char **argv) {
	
	if (argc != 2) {
		std::cout << "Harl don't know what to do with this amount of parameters." << std::endl;
		std::cout << "Usage: ./harlFilter <complain>" << std::endl;
		return 1;
	}

	Harl harl;

	harl.complain(std::string(argv[1]));

	return 0;
}