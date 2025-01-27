#include <iostream>
#include "../includes/Cat.hpp"

Cat::Cat(void) : Animal() {
	this->_type = "Cat";
	std::cout << "Cat default constructor called" << std::endl;
}

Cat::Cat(Cat const &src) : Animal(src) {
	std::cout << "Cat copy constructor called" << std::endl;
}

Cat::~Cat(void) {
	std::cout << "Cat destructor called" << std::endl;
}

Cat &Cat::operator=(Cat const &rhs) {
	std::cout << "Assignment operator called" << std::endl;
	if (this != &rhs) {
		Animal::operator=(rhs);
	}
	return *this;
}

void Cat::makeSound(void) const {
	std::cout << "*miau miau*" << std::endl;
}

// -------------------------------Wrong Cat------------------------------------

WrongCat::WrongCat(void) : WrongAnimal() {
	this->_type = "WrongCat";
	std::cout << "WrongCat default constructor called" << std::endl;
}

WrongCat::WrongCat(WrongCat const &src) : WrongAnimal(src) {
	std::cout << "WrongCat copy constructor called" << std::endl;
}

WrongCat::~WrongCat(void) {
	std::cout << "WrongCat destructor called" << std::endl;
}

WrongCat &WrongCat::operator=(WrongCat const &rhs) {
	if (this != &rhs) {
		WrongAnimal::operator=(rhs);
	}
	return *this;
}

void WrongCat::makeSound(void) const {
	std::cout << "*Wrong Cat Wrong Cat*" << std::endl;
}