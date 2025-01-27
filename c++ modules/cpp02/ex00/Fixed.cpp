#include <iostream>
#include "Fixed.hpp"

Fixed::Fixed() : _fpValue(0) {
	std::cout << "Default contructor called" << std::endl;
}

Fixed::Fixed(Fixed const &src) {
	std::cout << "Copy contructor called" << std::endl;
	*this = src;
}

// dostosować do aktualnego zadania
Fixed &Fixed::operator=(Fixed const &rhs) {
	std::cout << "Assignment operator called" << std::endl;
	if (this != &rhs)
		this->_fpValue = rhs.getRawBits();
	return *this;
}

Fixed::~Fixed() {
	std::cout << "Destructor called" << std::endl;
}

int Fixed::getRawBits(void) const {
	std::cout << "getRawBits member function called" << std::endl;
	return this->_fpValue;
}

void Fixed::setRawBits(int const raw) {
	std::cout << "setRawBits member function called" << std::endl;
	this->_fpValue = raw;
}

const int Fixed::_bits = 8;