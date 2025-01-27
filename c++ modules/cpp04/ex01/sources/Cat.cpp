#include <iostream>
#include "../includes/Cat.hpp"

Cat::Cat(void) : Animal() {
	this->_type = "Cat";
	this->brain = new Brain();
	std::cout << "Cat default constructor called" << std::endl;
}

Cat::Cat(Cat const &src) : Animal(src) {
	std::cout << "Cat copy constructor called" << std::endl;
	this->brain = new Brain(*src.brain);
}

Cat::~Cat(void) {
	std::cout << "Cat destructor called" << std::endl;
	delete this->brain;
}

Cat &Cat::operator=(Cat const &rhs) {
	std::cout << "Assignment operator called" << std::endl;
	if (this != &rhs) {
		Animal::operator=(rhs);
		delete this->brain;
		this->brain = new Brain(*rhs.brain);
	}
	return *this;
}

Brain *Cat::getBrain(void) const {
	return this->brain;
}

void Cat::makeSound(void) const {
	std::cout << "*miau miau*" << std::endl;
}
