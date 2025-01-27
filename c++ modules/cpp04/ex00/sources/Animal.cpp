#include <iostream>
#include "../includes/Animal.hpp"

Animal::Animal(void) : _type("") {
	std::cout << "Animal default constructor called" << std::endl;
}

Animal::Animal(Animal const &src) {
	std::cout << "Animal copy constructor called" << std::endl;
	*this = src;
}

Animal::~Animal(void) {
	std::cout << "Animal destructor called" << std::endl;
}

Animal &Animal::operator=(Animal const &rhs) {
	std::cout << "Assignment operator called" << std::endl;
	if (this != &rhs) {
		this->_type = rhs._type;
	}
	return *this;
}

std::string Animal::getType() const {
	return this->_type;
}

void Animal::makeSound(void) const {
	std::cout << "*some kind of animal sounds*" << std::endl;
}

// -----------------------------Wrong Animal-----------------------------------

WrongAnimal::WrongAnimal(void) : _type("") {
	std::cout << "WrongAnimal default constructor called" << std::endl;
}

WrongAnimal::WrongAnimal(WrongAnimal const &src) {
	std::cout << "WrongAnimal copy constructor called" << std::endl;
	*this = src;
}

WrongAnimal::~WrongAnimal(void) {
	std::cout << "WrongAnimal destructor called" << std::endl;
}

WrongAnimal &WrongAnimal::operator=(WrongAnimal const &rhs) {
	if (this != &rhs) {
		this->_type = rhs._type;
	}
	return *this;
}

std::string WrongAnimal::getType() const {
	return this->_type;
}

void WrongAnimal::makeSound(void) const {
	std::cout << "*WrongAnimal sounds*" << std::endl;
}
