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

		// Comparison operators
		bool operator>(const Fixed &rhs) const;
		bool operator>=(const Fixed &rhs) const;
		bool operator<(const Fixed &rhs) const;
		bool operator<=(const Fixed &rhs) const;
		bool operator==(const Fixed &rhs) const;
		bool operator!=(const Fixed &rhs) const;

		// Arithmetic operators
		Fixed operator+(const Fixed &rhs) const;
		Fixed operator-(const Fixed &rhs) const;
		Fixed operator*(const Fixed &rhs) const;
		Fixed operator/(const Fixed &rhs) const;

		// Prefix operators
		Fixed &operator++();
		Fixed &operator--();

		// Postfix operators
		Fixed operator++(int);
		Fixed operator--(int);

		// Methods
		int		getRawBits(void) const;
		void	setRawBits(int const raw);
		float	toFloat(void) const;
		int		toInt(void) const;

		// Static methods
		static const Fixed	min(Fixed &a, Fixed &b);
		static const Fixed	min(Fixed const &a, Fixed const &b);
		static const Fixed	max(Fixed &a, Fixed &b);
		static const Fixed	max(Fixed const &a, Fixed const &b);
};

std::ostream &operator<<(std::ostream &out, const Fixed &fixed);

#endif