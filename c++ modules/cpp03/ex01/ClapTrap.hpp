#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <iostream>

class ClapTrap {
	protected:
		std::string _name;
		int	_hp;
		int _energyPoints;
		int _attackDamage;

	public:
		// Conctructors and Destructor
		ClapTrap(void);		// Default construcotr (CANNON)
		ClapTrap(std::string name); // Set constructor
		ClapTrap(const ClapTrap &src);	// Copy construcor (CANNON)
		virtual ~ClapTrap(void);	// Destructor (CANNON)

		// Overloads
		ClapTrap &operator=(const ClapTrap &rhs); // Assign operator (CANNON)

		// Methods
		virtual void attack(const std::string& target);
		void takeDamage(unsigned int amount);
		void beRepaired(unsigned int amount);
};

#endif