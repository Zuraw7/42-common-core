#include "./RPN.hpp"

RPN::RPN() {}

RPN::RPN(RPN const &src) {
	*this = src;
}

RPN::~RPN() {}

RPN &RPN::operator=(RPN const &rhs) {
	if (this != &rhs) {
		this->rpn_stack = rhs.rpn_stack;
	}
	return *this;
}

void RPN::pushToStack(double number) {
	this->rpn_stack.push(number);
}

int RPN::calculate(char oper) {
	if (this->rpn_stack.size() < 2) {
		std::cout << "Error: Not enough operands in stack to perform operation '" << oper << "'." << std::endl;
		return 1;
	}

	double right = this->rpn_stack.top();
	this->rpn_stack.pop();
	double left = this->rpn_stack.top();
	this->rpn_stack.pop();

	if (oper == '/') {
		if (right == 0) {
			std::cerr << "Error: Division by zero." << std::endl;
			return 1;
		}
		this->rpn_stack.push(left / right);
	} else if (oper == '*') {
		this->rpn_stack.push(left * right);
	} else if (oper == '-') {
		this->rpn_stack.push(left - right);
	} else if (oper == '+') {
		this->rpn_stack.push(left + right);
	}
	return 0;
}

double RPN::getResult() {
	if (this->rpn_stack.size() > 1) {
		throw std::runtime_error("Error: The stack does not contain exactly one result.");
	}
	return this->rpn_stack.top();
}