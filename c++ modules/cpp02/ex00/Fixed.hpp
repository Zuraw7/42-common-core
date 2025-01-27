#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

class Fixed {

	private:
		int					_fpValue;	// fixed point value
		static const int	_bits;

	public:
		Fixed();								// Default constructor
		Fixed(Fixed const &src);				// Copy constructor
		Fixed &operator = (Fixed const &rhs);	// Copy assignment operator
		~Fixed();								// Destructor

	int getRawBits(void) const;
	void setRawBits(int const raw);
};

#endif