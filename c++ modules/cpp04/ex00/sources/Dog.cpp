#include <iostream>
#include "../includes/Dog.hpp"

Dog::Dog(void) : Animal() {
	this->_type = "Dog";
	std::cout << "Dog default constructor called" << std::endl;
}

Dog::Dog(Dog const &src) : Animal(src) {
	std::cout << "Dog copy constructor called" << std::endl;
}

Dog::~Dog(void) {
	std::cout << "Dog destructor called" << std::endl;
}

Dog &Dog::operator=(Dog const &rhs) {
	std::cout << "Assignment operator called" << std::endl;
	if (this != &rhs) {
		Animal::operator=(rhs);
	}
	return *this;
}

void Dog::makeSound(void) const {
	std::cout << "*woof woof*" << std::endl;
}