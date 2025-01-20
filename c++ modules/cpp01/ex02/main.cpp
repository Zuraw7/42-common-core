#include <iostream>

int main(void) {
	std::string str = "HI THIS IS BRAIN";
	std::string *stringPTR = &str;
	std::string &stringREF = str;

	std::cout << "str memory address:\t" << "stringPTR memory address held\t" << "stringREF memory address held" << std::endl;
	std::cout << &str << "\t\t" << stringPTR << "\t\t\t" << &stringREF << std::endl << std::endl;

	std::cout << "str value:\t\t" << "stringPTR pointed value\t\t" << "stringREF pointed value" << std::endl;
	std::cout << str << "\t" << *stringPTR << "\t\t" << stringREF << std::endl;

	return 0;
}