#include <iostream>
#include <exception>
#include <algorithm>
#include "Span.hpp"

Span::Span() {}
Span::~Span() {}

Span::Span(unsigned int n) :_nbLimit(n) {
	this->_numbers.reserve(n);
}

Span::Span(Span const &src) : _nbLimit(src._nbLimit), _numbers(src._numbers) {
	*this = src;
}

Span &Span::operator=(Span const &rhs) {
	if (this != &rhs) {
		this->_nbLimit = rhs._nbLimit;
		this->_numbers = rhs._numbers;
	}
	return *this;
}

void Span::addNumber(int number) {
	if (this->_numbers.size() < this->_nbLimit) {
		this->_numbers.push_back(number);
		std::cout << "Added " << number << " at index " << this->_numbers.size() - 1 << std::endl;
	} else {
		throw std::out_of_range("Numbers vector is full!");
	}
}

void Span::addNumber(std::vector<int>::iterator begin, std::vector<int>::iterator end) {
	if (this->_numbers.size() + std::distance(begin, end) > this->_nbLimit) {
		throw std::overflow_error("Adding numbers would exceed the limit of Span!");
	}
	this->_numbers.insert(this->_numbers.end(), begin, end);
}

int Span::shortestSpan() {
	if (this->_numbers.size() < 2) {
		throw Span::NotEnoughNumbers();
	}

	std::vector<int> sorted = this->_numbers;
	std::sort(sorted.begin(), sorted.end());
	int diff = sorted[1] - sorted[0];
	int smallestDiff = diff;

	for (size_t i = 1; i < sorted.size(); i++) {
		diff = sorted[i] - sorted[i - 1];
		if (diff < smallestDiff) {
			smallestDiff = diff;
		}
	}

	return smallestDiff;
}

int Span::longestSpan() {
	if (this->_nbLimit < 2) {
		throw Span::NotEnoughNumbers();
	}

	std::vector<int> sorted = this->_numbers;
	
	std::sort(sorted.begin(), sorted.end());

	return sorted[sorted.size() - 1] - sorted[0];
}
