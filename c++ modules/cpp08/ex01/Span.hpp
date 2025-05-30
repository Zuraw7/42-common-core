#ifndef SPAN_HPP
#define SPAN_HPP

#include <iostream>
#include <vector>
#include <exception>

class Span {
	private:
		Span();
		unsigned int	_nbLimit;
		std::vector<int> _numbers;

	public:
		Span(unsigned int n);
		Span(Span const &src);
		~Span();

		Span &operator=(Span const &rhs);

		class NotEnoughNumbers : public std::exception {
			public:
				virtual const char* what() const throw() {
					return ("2 numbers at least required");
				}
		};

		void addNumber(int number);
		int shortestSpan();
		int longestSpan();
		void addNumber(std::vector<int>::iterator begin, std::vector<int>::iterator end);
};

#endif