#include <iostream>
#include "../includes/Dog.hpp"

Dog::Dog(void) : Animal() {
	this->_type = "Dog";
	this->brain = new Brain();
	std::cout << "Dog default constructor called" << std::endl;
}

Dog::Dog(Dog const &src) : Animal(src) {
	std::cout << "Dog copy constructor called" << std::endl;
	this->brain = new Brain(*src.brain);
}

Dog::~Dog(void) {
	std::cout << "Dog destructor called" << std::endl;
	delete this->brain;
}

Dog &Dog::operator=(Dog const &rhs) {
	std::cout << "Assignment operator called" << std::endl;
	if (this != &rhs) {
		Animal::operator=(rhs);
		delete this->brain;
		this->brain = new Brain(*rhs.brain);
	}
	return *this;
}

Brain *Dog::getBrain(void) const {
	return this->brain;
}

void Dog::makeSound(void) const {
	std::cout << "*woof woof*" << std::endl;
}