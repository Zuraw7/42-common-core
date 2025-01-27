#include <iostream>
#include <cmath>
#include "Fixed.hpp"

// Canons
Fixed::Fixed() : _fpValue(0) {
	// std::cout << "Default contructor called" << std::endl;
}

Fixed::Fixed(Fixed const &src) {
	// std::cout << "Copy contructor called" << std::endl;
	*this = src;
}

Fixed &Fixed::operator=(Fixed const &rhs) {
	// std::cout << "Assignment operator called" << std::endl;
	if (this != &rhs)
		this->_fpValue = rhs.getRawBits();
	return *this;
}

Fixed::~Fixed() {
	// std::cout << "Destructor called" << std::endl;
}

// Overloads
Fixed::Fixed(const int i) {
	// std::cout << "Int constructor called" << std::endl;
	this->_fpValue = i << _bits;
}

Fixed::Fixed(const float f) {
	// std::cout << "Float constructor called" << std::endl;
	this->_fpValue = static_cast<int>(round(f * (1 << _bits)));
}

std::ostream &operator<<(std::ostream &out, const Fixed &fixed) {
	out << fixed.toFloat();
	return out;
}

// - comparison
bool Fixed::operator>(const Fixed &rhs) const {
	return this->_fpValue > rhs._fpValue;
}

bool Fixed::operator>=(const Fixed &rhs) const {
	return this->_fpValue >= rhs._fpValue;
}

bool Fixed::operator<(const Fixed &rhs) const {
	return this->_fpValue < rhs._fpValue;
}

bool Fixed::operator<=(const Fixed &rhs) const {
	return this->_fpValue <= rhs._fpValue;
}

bool Fixed::operator==(const Fixed &rhs) const {
	return this->_fpValue == rhs._fpValue;
}

bool Fixed::operator!=(const Fixed &rhs) const {
	return this->_fpValue != rhs._fpValue;
}

// - arithmetic
Fixed Fixed::operator+(const Fixed &rhs) const {
	Fixed result;

	result._fpValue = this->_fpValue + rhs._fpValue;
	return result;
}

Fixed Fixed::operator-(const Fixed &rhs) const {
	Fixed result;

	result._fpValue = this->_fpValue - rhs._fpValue;
	return result;
}

Fixed Fixed::operator*(const Fixed &rhs) const {
	Fixed result;

	result._fpValue = (this->_fpValue * rhs._fpValue) >> _bits;
	return result;
}

Fixed Fixed::operator/(const Fixed &rhs) const {
	Fixed result;

	result._fpValue = (this->_fpValue << _bits) / rhs._fpValue;
	return result;
}

// - prefix
Fixed &Fixed::operator++() {
	this->_fpValue++;
	return *this;
}

Fixed &Fixed::operator--() {
	this->_fpValue--;
	return *this;
}

// - postfix
Fixed Fixed::operator++(int) {
	Fixed temp = *this;
	this->_fpValue++;
	return temp;
}

Fixed Fixed::operator--(int) {
	Fixed temp = *this;
	this->_fpValue--;
	return temp;
}

// Methods
int Fixed::getRawBits(void) const {
	return this->_fpValue;
}

void Fixed::setRawBits(int const raw) {
	// std::cout << "setRawBits member function called" << std::endl;
	this->_fpValue = raw;
}

float Fixed::toFloat(void) const {
	return static_cast<float>(this->_fpValue) / (1 << _bits);
}

int Fixed::toInt(void) const {
	return this->_fpValue >> _bits;
}

Fixed Fixed::min(Fixed &a, Fixed &b) {
	if (a > b)
		return b;
	return a;
}

Fixed const Fixed::min(Fixed const &a, Fixed const &b) {
	if (a > b)
		return b;
	return a;
}

Fixed Fixed::max(Fixed &a, Fixed &b) {
	if (a < b)
		return b;
	return a;
}

Fixed const Fixed::max(Fixed const &a, Fixed const &b) {
	if (a < b)
		return b;
	return a;
}

const int Fixed::_bits = 8;