#include <iostream>
#include <cmath>
#include "./Point.hpp"

// Default contructor
Point::Point(void) : _x(0), _y(0) {
	std::cout << "Default contructor called" << std::endl;
}

// Set contructor
Point::Point(float const x, float const y) : _x(x), _y(y) {
	std::cout << "Set contructor called" << std::endl;
}

// Copy constructor
Point::Point(Point const &src) : _x(src.getX()), _y(src.getY()) {
	std::cout << "Copy contructor called" << std::endl;
}

// Assignment constructor
Point &Point::operator = (Point const &rhs) {
	// It is not possible to assign to const values like _x and _y here
	// so just return original
	(void) rhs;
	std::cout << "You cannot assing to const values, nothing changed" << std::endl;
	return *this;
}

// Destructor
Point::~Point(void) {
	std::cout << "Destructor called" << std::endl;
}

// Getters
const Fixed Point::getX(void) const {
	return (this->_x);
}

const Fixed Point::getY(void) const {
	return (this->_y);
}
