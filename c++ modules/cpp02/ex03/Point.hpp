#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>
#include <cmath>
#include "./Fixed.hpp"

class Point {
	private:
		const Fixed _x;
		const Fixed _y;

	public:
		// Cannons
		Point(void);	// Default constructor
		Point(Point const &src);	// Copy constructor
		Point &operator = (Point const &rhs); // Assignment contructor
		~Point(void);	// Destructor

		// Methods
		Point(float const x, float const y);

		// Getters
		const Fixed getX(void) const;
		const Fixed getY(void) const;
};

#endif