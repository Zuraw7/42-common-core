#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <sstream>
#include <exception>

class RPN {
	private:
		std::stack<double> rpn_stack;

	public:
		RPN();
		RPN(RPN const &src);
		~RPN();

		RPN &operator=(RPN const &rhs);

		void pushToStack(double number);
		int calculate(char oper);
		double getResult();
};

#endif