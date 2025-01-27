#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

class Fixed {

	private:
		int					_fpValue;	// fixed point value
		static const int	_bits;

	public:
		// Canons
		Fixed();								// Default constructor
		Fixed(Fixed const &src);				// Copy constructor
		Fixed &operator = (Fixed const &rhs);	// Copy assignment operator
		~Fixed();								// Destructor

		// Overloads
		Fixed(int i);						// Default contructor with int
		Fixed(float f);						// Default contructor with float

		// Methods
		int		getRawBits(void) const;
		void	setRawBits(int const raw);
		float	toFloat(void) const;
		int		toInt(void) const;
};

std::ostream &operator<<(std::ostream &out, const Fixed &fixed);

#endif