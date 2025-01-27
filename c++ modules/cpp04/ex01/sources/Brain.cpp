#include <iostream>
#include "../includes/Brain.hpp"

Brain::Brain(void) {
	std::cout << "Brain default constructor called" << std::endl;
	for (int i = 0; i < 100; i++) {
		this->_ideas[i] = "";
	}
}

Brain::Brain(Brain const &src) {
	std::cout << "Brain copy constructor called" << std::endl;
	*this = src;
}

Brain::~Brain(void) {
	std::cout << "Brain destructor called" << std::endl;
}

Brain &Brain::operator=(Brain const &rhs) {
	std::cout << "Assignment operator called" << std::endl;
	if (this != &rhs) {
		for (int i = 0; i < 100; i++) {
			this->_ideas[i] = rhs._ideas[i];
		}
	}
	return *this;
}

std::string Brain::getIdea(int i) const {
	if (i < 0 || i >= 100) {
		std::cerr << "Error: Invalid index passed to getIdea()." << std::endl;
		return "";
	}
	return this->_ideas[i];
}

void Brain::setIdea(const std::string &idea, int i) {
	if (i < 0 || i >= 100) {
		std::cerr << "Error: Invalid index passed to setIdea()." << std::endl;
		return ;
	}
	this->_ideas[i] = idea;
}