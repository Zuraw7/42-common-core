#include <iostream>
#include <cmath>
#include "Fixed.hpp"

// Canons
Fixed::Fixed() : _fpValue(0) {
	std::cout << "Default contructor called" << std::endl;
}

Fixed::Fixed(Fixed const &src) {
	std::cout << "Copy contructor called" << std::endl;
	*this = src;
}

Fixed &Fixed::operator=(Fixed const &rhs) {
	std::cout << "Assignment operator called" << std::endl;
	if (this != &rhs)
		this->_fpValue = rhs.getRawBits();
	return *this;
}

Fixed::~Fixed() {
	std::cout << "Destructor called" << std::endl;
}

// Overloads
Fixed::Fixed(const int i) {
	std::cout << "Int constructor called" << std::endl;
	this->_fpValue = i << _bits;
}

Fixed::Fixed(const float f) {
	std::cout << "Float constructor called" << std::endl;
	this->_fpValue = static_cast<int>(round(f * (1 << _bits)));
}

std::ostream &operator<<(std::ostream &out, const Fixed &fixed) {
	out << fixed.toFloat();
	return out;
}

// Methods
int Fixed::getRawBits(void) const {
	return this->_fpValue;
}

void Fixed::setRawBits(int const raw) {
	std::cout << "setRawBits member function called" << std::endl;
	this->_fpValue = raw;
}

float Fixed::toFloat(void) const {
	return static_cast<float>(this->_fpValue) / (1 << _bits);
}

int Fixed::toInt(void) const {
	return this->_fpValue >> _bits;
}

const int Fixed::_bits = 8;