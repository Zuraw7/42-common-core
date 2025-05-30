#include "./RPN.hpp"

static bool isAllowed(const char c, const std::string &set);
bool isValidInput(const char *argv);
int doRPN(const char *argv, RPN &rpn);

int main (int argc, char **argv) {

	if (argc != 2) {
		std::cerr << "Error: Bad input!" << std::endl;
		std::cout << "Usage: ./RPN \"Reverse Polish Notation\"" << std::endl;
		return 1;
	}

	if (!isValidInput(argv[1])) {
		std::cerr << "Error: Given Reverse Polish Notation is incorrect!" << std::endl;
		return 1;
	}

	RPN rpn;

	if (doRPN(argv[1], rpn) == 1) {
		return 1;
	}

	try {
		std::cout << rpn.getResult() << std::endl;
	} catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}

static bool isAllowed(const char c, const std::string &set) {
	return set.find(c) != std::string::npos;
}

bool isValidInput(const char *argv) {
	std::string input(argv);
	std::string allowed = "0123456789 \t\n\v\r*/-+";

	for (int i = 0; argv[i]; i++) {
		if (!isAllowed(argv[i], allowed)) {
			return false;
		}
	}
	return true;
}

int doRPN(const char *argv, RPN &rpn) {
	std::string input(argv), token;
	std::istringstream ss(input);
	
	while (ss >> token) {
		if ((token.size() > 1 && token[0] != '-' && !(std::isdigit(token[1] - '0'))) || token.size() > 2) {
			std::cerr << "Error: One sign + space only" << std::endl;
			return 1;
		}
		if (token[0] == '-' || token[0] == '+' || token[0] == '*' || token[0] == '/') {
			if (rpn.calculate(token[0]) == 1) {
				return 1;
			}
		} else {
			rpn.pushToStack(token[0] - '0');
		}
	}
	return 0;
}
