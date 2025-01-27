#include <iostream>
#include "../includes/Animal.hpp"

AAnimal::AAnimal(void) : _type("") {
	std::cout << "AAnimal default constructor called" << std::endl;
}

AAnimal::AAnimal(AAnimal const &src) {
	std::cout << "AAnimal copy constructor called" << std::endl;
	*this = src;
}

AAnimal::~AAnimal(void) {
	std::cout << "AAnimal destructor called" << std::endl;
}

AAnimal &AAnimal::operator=(AAnimal const &rhs) {
	std::cout << "Assignment operator called" << std::endl;
	if (this != &rhs) {
		this->_type = rhs._type;
	}
	return *this;
}

std::string AAnimal::getType() const {
	return this->_type;
}

