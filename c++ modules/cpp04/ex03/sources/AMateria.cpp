#include <iostream>
#include "../includes/AMateria.hpp"

// ---------------------------------------AMateria-------------------------------------

AMateria::AMateria() : _type("Default") {
	// std::cout << "AMateria defaut constructor called" << std::endl;
}

AMateria::AMateria(std::string const & type) : _type(type) {
	// std::cout << "AMateria set constructor called" << std::endl;
}

AMateria::AMateria(AMateria const &src) {
	// std::cout << "AMateria copy constructor called" << std::endl;
	*this = src;
}

AMateria::~AMateria() {
	// std::cout << "AMateria destructor called" << std::endl;
}

AMateria &AMateria::operator=(AMateria const &rhs) {
	// std::cout << "AMateria assignment operator called" << std::endl;
	if (this != &rhs) {
	}
	return *this;
}

std::string const &AMateria::getType() const {
	return this->_type;
}

void AMateria::use(ICharacter& target) {
	std::cout << "Default materia does nothing on " << target.getName() << "!" << std::endl;
}

// ---------------------------------------ICE-------------------------------------------

Ice::Ice() {
	// std::cout << "Ice defaut constructor called" << std::endl;
	this->_type = "ice";
}

Ice::Ice(Ice const &src) : AMateria(src) {
	// std::cout << "Ice copy constructor called" << std::endl;
	this->_type = src.getType();
}

Ice::~Ice() {
	// std::cout << "Ice destructor called" << std::endl;
}

Ice &Ice::operator=(Ice const &rhs) {
	// std::cout << "Ice assignment operator called" << std::endl;
	if (this != &rhs) {
		AMateria::operator=(rhs);
	}
	return *this;
}

AMateria* Ice::clone() const {
	return new Ice(*this);
}

void Ice::use(ICharacter& target) {
	std::cout << "* shoots an ice bolt at " << target.getName() << " *" << std::endl;
}

// --------------------------------------CURE-------------------------------------------

Cure::Cure() {
	// std::cout << "Cure defaut constructor called" << std::endl;
	this->_type = "cure";
}

Cure::Cure(Cure const &src) : AMateria(src) {
	// std::cout << "Cure copy constructor called" << std::endl;
	this->_type = src.getType();
}

Cure::~Cure() {
	// std::cout << "Cure destructor called" << std::endl;
}

Cure &Cure::operator=(Cure const &rhs) {
	// std::cout << "Cure assignment operator called" << std::endl;
	if (this != &rhs) {
		AMateria::operator=(rhs);
	}
	return *this;
}

AMateria* Cure::clone() const {
	return new Cure(*this);
}

void Cure::use(ICharacter& target) {
	std::cout << "* heals " << target.getName() << "'s wounds *" << std::endl;
}